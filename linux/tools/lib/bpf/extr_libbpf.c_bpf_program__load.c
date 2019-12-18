#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr; int* fds; } ;
struct bpf_program {int (* preprocessor ) (struct bpf_program*,int,int /*<<< orphan*/ ,scalar_t__,struct bpf_prog_prep_result*) ;scalar_t__ insns_cnt; int /*<<< orphan*/  insns; int /*<<< orphan*/  section_name; TYPE_1__ instances; } ;
struct bpf_prog_prep_result {int* pfd; scalar_t__ new_insn_cnt; int /*<<< orphan*/  new_insn_ptr; } ;
typedef  int /*<<< orphan*/  result ;
typedef  int (* bpf_program_prep_t ) (struct bpf_program*,int,int /*<<< orphan*/ ,scalar_t__,struct bpf_prog_prep_result*) ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int LIBBPF_ERRNO__INTERNAL ; 
 int load_program (struct bpf_program*,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (struct bpf_prog_prep_result*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

int
bpf_program__load(struct bpf_program *prog,
		  char *license, __u32 kern_version)
{
	int err = 0, fd, i;

	if (prog->instances.nr < 0 || !prog->instances.fds) {
		if (prog->preprocessor) {
			pr_warning("Internal error: can't load program '%s'\n",
				   prog->section_name);
			return -LIBBPF_ERRNO__INTERNAL;
		}

		prog->instances.fds = malloc(sizeof(int));
		if (!prog->instances.fds) {
			pr_warning("Not enough memory for BPF fds\n");
			return -ENOMEM;
		}
		prog->instances.nr = 1;
		prog->instances.fds[0] = -1;
	}

	if (!prog->preprocessor) {
		if (prog->instances.nr != 1) {
			pr_warning("Program '%s' is inconsistent: nr(%d) != 1\n",
				   prog->section_name, prog->instances.nr);
		}
		err = load_program(prog, prog->insns, prog->insns_cnt,
				   license, kern_version, &fd);
		if (!err)
			prog->instances.fds[0] = fd;
		goto out;
	}

	for (i = 0; i < prog->instances.nr; i++) {
		struct bpf_prog_prep_result result;
		bpf_program_prep_t preprocessor = prog->preprocessor;

		memset(&result, 0, sizeof(result));
		err = preprocessor(prog, i, prog->insns,
				   prog->insns_cnt, &result);
		if (err) {
			pr_warning("Preprocessing the %dth instance of program '%s' failed\n",
				   i, prog->section_name);
			goto out;
		}

		if (!result.new_insn_ptr || !result.new_insn_cnt) {
			pr_debug("Skip loading the %dth instance of program '%s'\n",
				 i, prog->section_name);
			prog->instances.fds[i] = -1;
			if (result.pfd)
				*result.pfd = -1;
			continue;
		}

		err = load_program(prog, result.new_insn_ptr,
				   result.new_insn_cnt,
				   license, kern_version, &fd);

		if (err) {
			pr_warning("Loading the %dth instance of program '%s' failed\n",
					i, prog->section_name);
			goto out;
		}

		if (result.pfd)
			*result.pfd = fd;
		prog->instances.fds[i] = fd;
	}
out:
	if (err)
		pr_warning("failed to load program '%s'\n",
			   prog->section_name);
	zfree(&prog->insns);
	prog->insns_cnt = 0;
	return err;
}