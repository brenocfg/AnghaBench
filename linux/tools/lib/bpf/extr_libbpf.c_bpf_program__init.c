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
struct TYPE_2__ {int nr; int /*<<< orphan*/ * fds; } ;
struct bpf_program {size_t insns_cnt; int idx; int /*<<< orphan*/  type; TYPE_1__ instances; int /*<<< orphan*/  insns; int /*<<< orphan*/  pin_name; int /*<<< orphan*/  section_name; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_UNSPEC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __bpf_program__pin_name (struct bpf_program*) ; 
 int /*<<< orphan*/  bpf_program__exit (struct bpf_program*) ; 
 int /*<<< orphan*/  malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memset (struct bpf_program*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int
bpf_program__init(void *data, size_t size, char *section_name, int idx,
		  struct bpf_program *prog)
{
	const size_t bpf_insn_sz = sizeof(struct bpf_insn);

	if (size == 0 || size % bpf_insn_sz) {
		pr_warning("corrupted section '%s', size: %zu\n",
			   section_name, size);
		return -EINVAL;
	}

	memset(prog, 0, sizeof(*prog));

	prog->section_name = strdup(section_name);
	if (!prog->section_name) {
		pr_warning("failed to alloc name for prog under section(%d) %s\n",
			   idx, section_name);
		goto errout;
	}

	prog->pin_name = __bpf_program__pin_name(prog);
	if (!prog->pin_name) {
		pr_warning("failed to alloc pin name for prog under section(%d) %s\n",
			   idx, section_name);
		goto errout;
	}

	prog->insns = malloc(size);
	if (!prog->insns) {
		pr_warning("failed to alloc insns for prog under section %s\n",
			   section_name);
		goto errout;
	}
	prog->insns_cnt = size / bpf_insn_sz;
	memcpy(prog->insns, data, size);
	prog->idx = idx;
	prog->instances.fds = NULL;
	prog->instances.nr = -1;
	prog->type = BPF_PROG_TYPE_UNSPEC;

	return 0;
errout:
	bpf_program__exit(prog);
	return -ENOMEM;
}