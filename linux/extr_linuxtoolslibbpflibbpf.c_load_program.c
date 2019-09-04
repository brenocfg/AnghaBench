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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_load_program_attr {int prog_type; int expected_attach_type; char const* name; int insns_cnt; char* license; int prog_ifindex; struct bpf_insn* insns; int /*<<< orphan*/  kern_version; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int BPF_MAXINSNS ; 
 scalar_t__ BPF_PROG_TYPE_KPROBE ; 
 int EINVAL ; 
 int LIBBPF_ERRNO__KVER ; 
 int LIBBPF_ERRNO__LOAD ; 
 int LIBBPF_ERRNO__PROG2BIG ; 
 int LIBBPF_ERRNO__PROGTYPE ; 
 int LIBBPF_ERRNO__VERIFY ; 
 int STRERR_BUFSIZE ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 char* str_error (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
load_program(enum bpf_prog_type type, enum bpf_attach_type expected_attach_type,
	     const char *name, struct bpf_insn *insns, int insns_cnt,
	     char *license, u32 kern_version, int *pfd, int prog_ifindex)
{
	struct bpf_load_program_attr load_attr;
	char *cp, errmsg[STRERR_BUFSIZE];
	char *log_buf;
	int ret;

	memset(&load_attr, 0, sizeof(struct bpf_load_program_attr));
	load_attr.prog_type = type;
	load_attr.expected_attach_type = expected_attach_type;
	load_attr.name = name;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = license;
	load_attr.kern_version = kern_version;
	load_attr.prog_ifindex = prog_ifindex;

	if (!load_attr.insns || !load_attr.insns_cnt)
		return -EINVAL;

	log_buf = malloc(BPF_LOG_BUF_SIZE);
	if (!log_buf)
		pr_warning("Alloc log buffer for bpf loader error, continue without log\n");

	ret = bpf_load_program_xattr(&load_attr, log_buf, BPF_LOG_BUF_SIZE);

	if (ret >= 0) {
		*pfd = ret;
		ret = 0;
		goto out;
	}

	ret = -LIBBPF_ERRNO__LOAD;
	cp = str_error(errno, errmsg, sizeof(errmsg));
	pr_warning("load bpf program failed: %s\n", cp);

	if (log_buf && log_buf[0] != '\0') {
		ret = -LIBBPF_ERRNO__VERIFY;
		pr_warning("-- BEGIN DUMP LOG ---\n");
		pr_warning("\n%s\n", log_buf);
		pr_warning("-- END LOG --\n");
	} else if (load_attr.insns_cnt >= BPF_MAXINSNS) {
		pr_warning("Program too large (%zu insns), at most %d insns\n",
			   load_attr.insns_cnt, BPF_MAXINSNS);
		ret = -LIBBPF_ERRNO__PROG2BIG;
	} else {
		/* Wrong program type? */
		if (load_attr.prog_type != BPF_PROG_TYPE_KPROBE) {
			int fd;

			load_attr.prog_type = BPF_PROG_TYPE_KPROBE;
			load_attr.expected_attach_type = 0;
			fd = bpf_load_program_xattr(&load_attr, NULL, 0);
			if (fd >= 0) {
				close(fd);
				ret = -LIBBPF_ERRNO__PROGTYPE;
				goto out;
			}
		}

		if (log_buf)
			ret = -LIBBPF_ERRNO__KVER;
	}

out:
	free(log_buf);
	return ret;
}