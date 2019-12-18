#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sysctl_test {scalar_t__ result; scalar_t__ fixup_value_insn; struct bpf_insn* insns; } ;
struct bpf_load_program_attr {char* license; struct bpf_insn* insns; int /*<<< orphan*/  insns_cnt; int /*<<< orphan*/  prog_type; } ;
struct bpf_insn {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_CGROUP_SYSCTL ; 
 scalar_t__ LOAD_REJECT ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char const*,int /*<<< orphan*/ ) ; 
 char const* bpf_log_buf ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fixup_sysctl_value (char*,int,struct bpf_insn*,scalar_t__) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  memset (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  probe_prog_length (struct bpf_insn*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int load_sysctl_prog_insns(struct sysctl_test *test,
				  const char *sysctl_path)
{
	struct bpf_insn *prog = test->insns;
	struct bpf_load_program_attr attr;
	int ret;

	memset(&attr, 0, sizeof(struct bpf_load_program_attr));
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL;
	attr.insns = prog;
	attr.insns_cnt = probe_prog_length(attr.insns);
	attr.license = "GPL";

	if (test->fixup_value_insn) {
		char buf[128];
		ssize_t len;
		int fd;

		fd = open(sysctl_path, O_RDONLY | O_CLOEXEC);
		if (fd < 0) {
			log_err("open(%s) failed", sysctl_path);
			return -1;
		}
		len = read(fd, buf, sizeof(buf));
		if (len == -1) {
			log_err("read(%s) failed", sysctl_path);
			close(fd);
			return -1;
		}
		close(fd);
		if (fixup_sysctl_value(buf, len, prog, test->fixup_value_insn))
			return -1;
	}

	ret = bpf_load_program_xattr(&attr, bpf_log_buf, BPF_LOG_BUF_SIZE);
	if (ret < 0 && test->result != LOAD_REJECT) {
		log_err(">>> Loading program error.\n"
			">>> Verifier output:\n%s\n-------\n", bpf_log_buf);
	}

	return ret;
}