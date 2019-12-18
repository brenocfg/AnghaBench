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
typedef  int /*<<< orphan*/  trace_program ;
typedef  int /*<<< orphan*/  test_skb ;
struct bpf_load_program_attr {char* license; int insns_cnt; int log_level; struct bpf_insn const* insns; int /*<<< orphan*/  prog_type; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  skb_program ;
typedef  int /*<<< orphan*/  error ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_DW ; 
 struct bpf_insn const BPF_EXIT_INSN () ; 
 struct bpf_insn const BPF_LDX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn const BPF_MOV64_IMM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_6 ; 
 struct bpf_insn const BPF_STX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_W ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,...) ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,int) ; 
 int bpf_prog_test_run (int,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bpf_raw_tracepoint_open (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 

void test_raw_tp_writable_test_run(void)
{
	__u32 duration = 0;
	char error[4096];

	const struct bpf_insn trace_program[] = {
		BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1, 0),
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_6, 0),
		BPF_MOV64_IMM(BPF_REG_0, 42),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	};

	struct bpf_load_program_attr load_attr = {
		.prog_type = BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE,
		.license = "GPL v2",
		.insns = trace_program,
		.insns_cnt = sizeof(trace_program) / sizeof(struct bpf_insn),
		.log_level = 2,
	};

	int bpf_fd = bpf_load_program_xattr(&load_attr, error, sizeof(error));
	if (CHECK(bpf_fd < 0, "bpf_raw_tracepoint_writable loaded",
		  "failed: %d errno %d\n", bpf_fd, errno))
		return;

	const struct bpf_insn skb_program[] = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	};

	struct bpf_load_program_attr skb_load_attr = {
		.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
		.license = "GPL v2",
		.insns = skb_program,
		.insns_cnt = sizeof(skb_program) / sizeof(struct bpf_insn),
	};

	int filter_fd =
		bpf_load_program_xattr(&skb_load_attr, error, sizeof(error));
	if (CHECK(filter_fd < 0, "test_program_loaded", "failed: %d errno %d\n",
		  filter_fd, errno))
		goto out_bpffd;

	int tp_fd = bpf_raw_tracepoint_open("bpf_test_finish", bpf_fd);
	if (CHECK(tp_fd < 0, "bpf_raw_tracepoint_writable opened",
		  "failed: %d errno %d\n", tp_fd, errno))
		goto out_filterfd;

	char test_skb[128] = {
		0,
	};

	__u32 prog_ret;
	int err = bpf_prog_test_run(filter_fd, 1, test_skb, sizeof(test_skb), 0,
				    0, &prog_ret, 0);
	CHECK(err != 42, "test_run",
	      "tracepoint did not modify return value\n");
	CHECK(prog_ret != 0, "test_run_ret",
	      "socket_filter did not return 0\n");

	close(tp_fd);

	err = bpf_prog_test_run(filter_fd, 1, test_skb, sizeof(test_skb), 0, 0,
				&prog_ret, 0);
	CHECK(err != 0, "test_run_notrace",
	      "test_run failed with %d errno %d\n", err, errno);
	CHECK(prog_ret != 0, "test_run_ret_notrace",
	      "socket_filter did not return 0\n");

out_filterfd:
	close(filter_fd);
out_bpffd:
	close(bpf_fd);
}