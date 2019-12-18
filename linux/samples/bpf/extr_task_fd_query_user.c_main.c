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
struct rlimit {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  buf ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_FD_TYPE_KPROBE ; 
 int /*<<< orphan*/  BPF_FD_TYPE_KRETPROBE ; 
 int /*<<< orphan*/  BPF_FD_TYPE_UPROBE ; 
 int /*<<< orphan*/  BPF_FD_TYPE_URETPROBE ; 
 int /*<<< orphan*/  CHECK_AND_RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 char* bpf_log_buf ; 
 int ksym_get_addr (char*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 scalar_t__ load_kallsyms () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  test_debug_fs_kprobe (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_debug_fs_uprobe (char*,int,int) ; 
 int /*<<< orphan*/  test_nondebug_fs_probe (char*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int main(int argc, char **argv)
{
	struct rlimit r = {1024*1024, RLIM_INFINITY};
	extern char __executable_start;
	char filename[256], buf[256];
	__u64 uprobe_file_offset;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	if (load_kallsyms()) {
		printf("failed to process /proc/kallsyms\n");
		return 1;
	}

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	/* test two functions in the corresponding *_kern.c file */
	CHECK_AND_RET(test_debug_fs_kprobe(0, "blk_mq_start_request",
					   BPF_FD_TYPE_KPROBE));
	CHECK_AND_RET(test_debug_fs_kprobe(1, "blk_account_io_completion",
					   BPF_FD_TYPE_KRETPROBE));

	/* test nondebug fs kprobe */
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x0, 0x0,
					     false, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, sizeof(buf)));
#ifdef __x86_64__
	/* set a kprobe on "bpf_check + 0x5", which is x64 specific */
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x5, 0x0,
					     false, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, sizeof(buf)));
#endif
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x0, 0x0,
					     true, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, sizeof(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", NULL, 0x0,
					     ksym_get_addr("bpf_check"), false,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, sizeof(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", NULL, 0x0,
					     ksym_get_addr("bpf_check"), false,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     NULL, 0));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", NULL, 0x0,
					     ksym_get_addr("bpf_check"), true,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, sizeof(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", NULL, 0x0,
					     ksym_get_addr("bpf_check"), true,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     0, 0));

	/* test nondebug fs uprobe */
	/* the calculation of uprobe file offset is based on gcc 7.3.1 on x64
	 * and the default linker script, which defines __executable_start as
	 * the start of the .text section. The calculation could be different
	 * on different systems with different compilers. The right way is
	 * to parse the ELF file. We took a shortcut here.
	 */
	uprobe_file_offset = (__u64)main - (__u64)&__executable_start;
	CHECK_AND_RET(test_nondebug_fs_probe("uprobe", (char *)argv[0],
					     uprobe_file_offset, 0x0, false,
					     BPF_FD_TYPE_UPROBE,
					     BPF_FD_TYPE_URETPROBE,
					     buf, sizeof(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("uprobe", (char *)argv[0],
					     uprobe_file_offset, 0x0, true,
					     BPF_FD_TYPE_UPROBE,
					     BPF_FD_TYPE_URETPROBE,
					     buf, sizeof(buf)));

	/* test debug fs uprobe */
	CHECK_AND_RET(test_debug_fs_uprobe((char *)argv[0], uprobe_file_offset,
					   false));
	CHECK_AND_RET(test_debug_fs_uprobe((char *)argv[0], uprobe_file_offset,
					   true));

	return 0;
}