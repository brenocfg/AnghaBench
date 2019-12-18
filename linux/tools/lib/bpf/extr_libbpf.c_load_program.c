#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bpf_program {scalar_t__ type; int /*<<< orphan*/  prog_flags; scalar_t__ log_level; int /*<<< orphan*/  line_info_cnt; int /*<<< orphan*/  line_info_rec_size; int /*<<< orphan*/  line_info; int /*<<< orphan*/  func_info_cnt; int /*<<< orphan*/  func_info_rec_size; int /*<<< orphan*/  func_info; TYPE_2__* obj; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  name; TYPE_1__* caps; scalar_t__ expected_attach_type; } ;
struct bpf_load_program_attr {scalar_t__ prog_type; int insns_cnt; char* license; int prog_btf_fd; scalar_t__ expected_attach_type; scalar_t__ log_level; int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  line_info_cnt; int /*<<< orphan*/  line_info_rec_size; int /*<<< orphan*/  line_info; int /*<<< orphan*/  func_info_cnt; int /*<<< orphan*/  func_info_rec_size; int /*<<< orphan*/  func_info; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  kern_version; struct bpf_insn* insns; int /*<<< orphan*/  name; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {scalar_t__ btf_ext; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 int BPF_LOG_BUF_SIZE ; 
 int BPF_MAXINSNS ; 
 scalar_t__ BPF_PROG_TYPE_KPROBE ; 
 int EINVAL ; 
 scalar_t__ ENOSPC ; 
 int LIBBPF_ERRNO__KVER ; 
 int LIBBPF_ERRNO__LOAD ; 
 int LIBBPF_ERRNO__PROG2BIG ; 
 int LIBBPF_ERRNO__PROGTYPE ; 
 int LIBBPF_ERRNO__VERIFY ; 
 int STRERR_BUFSIZE ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,int) ; 
 int bpf_object__btf_fd (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libbpf_strerror_r (scalar_t__,char*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (struct bpf_load_program_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

__attribute__((used)) static int
load_program(struct bpf_program *prog, struct bpf_insn *insns, int insns_cnt,
	     char *license, __u32 kern_version, int *pfd)
{
	struct bpf_load_program_attr load_attr;
	char *cp, errmsg[STRERR_BUFSIZE];
	int log_buf_size = BPF_LOG_BUF_SIZE;
	char *log_buf;
	int btf_fd, ret;

	if (!insns || !insns_cnt)
		return -EINVAL;

	memset(&load_attr, 0, sizeof(struct bpf_load_program_attr));
	load_attr.prog_type = prog->type;
	load_attr.expected_attach_type = prog->expected_attach_type;
	if (prog->caps->name)
		load_attr.name = prog->name;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = license;
	load_attr.kern_version = kern_version;
	load_attr.prog_ifindex = prog->prog_ifindex;
	/* if .BTF.ext was loaded, kernel supports associated BTF for prog */
	if (prog->obj->btf_ext)
		btf_fd = bpf_object__btf_fd(prog->obj);
	else
		btf_fd = -1;
	load_attr.prog_btf_fd = btf_fd >= 0 ? btf_fd : 0;
	load_attr.func_info = prog->func_info;
	load_attr.func_info_rec_size = prog->func_info_rec_size;
	load_attr.func_info_cnt = prog->func_info_cnt;
	load_attr.line_info = prog->line_info;
	load_attr.line_info_rec_size = prog->line_info_rec_size;
	load_attr.line_info_cnt = prog->line_info_cnt;
	load_attr.log_level = prog->log_level;
	load_attr.prog_flags = prog->prog_flags;

retry_load:
	log_buf = malloc(log_buf_size);
	if (!log_buf)
		pr_warning("Alloc log buffer for bpf loader error, continue without log\n");

	ret = bpf_load_program_xattr(&load_attr, log_buf, log_buf_size);

	if (ret >= 0) {
		if (load_attr.log_level)
			pr_debug("verifier log:\n%s", log_buf);
		*pfd = ret;
		ret = 0;
		goto out;
	}

	if (errno == ENOSPC) {
		log_buf_size <<= 1;
		free(log_buf);
		goto retry_load;
	}
	ret = -LIBBPF_ERRNO__LOAD;
	cp = libbpf_strerror_r(errno, errmsg, sizeof(errmsg));
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