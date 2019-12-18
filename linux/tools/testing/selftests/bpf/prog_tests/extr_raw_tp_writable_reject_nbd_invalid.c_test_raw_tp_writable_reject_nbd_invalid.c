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
struct nbd_request {int dummy; } ;
struct bpf_load_program_attr {char* license; int insns_cnt; int log_level; struct bpf_insn const* insns; int /*<<< orphan*/  prog_type; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  program ;
typedef  int /*<<< orphan*/  error ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_DW ; 
 struct bpf_insn const BPF_EXIT_INSN () ; 
 struct bpf_insn const BPF_LDX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_6 ; 
 scalar_t__ CHECK (int,char*,char*,...) ; 
 int bpf_load_program_xattr (struct bpf_load_program_attr*,char*,int) ; 
 int bpf_raw_tracepoint_open (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 

void test_raw_tp_writable_reject_nbd_invalid(void)
{
	__u32 duration = 0;
	char error[4096];
	int bpf_fd = -1, tp_fd = -1;

	const struct bpf_insn program[] = {
		/* r6 is our tp buffer */
		BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1, 0),
		/* one byte beyond the end of the nbd_request struct */
		BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_6,
			    sizeof(struct nbd_request)),
		BPF_EXIT_INSN(),
	};

	struct bpf_load_program_attr load_attr = {
		.prog_type = BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE,
		.license = "GPL v2",
		.insns = program,
		.insns_cnt = sizeof(program) / sizeof(struct bpf_insn),
		.log_level = 2,
	};

	bpf_fd = bpf_load_program_xattr(&load_attr, error, sizeof(error));
	if (CHECK(bpf_fd < 0, "bpf_raw_tracepoint_writable load",
		  "failed: %d errno %d\n", bpf_fd, errno))
		return;

	tp_fd = bpf_raw_tracepoint_open("nbd_send_request", bpf_fd);
	if (CHECK(tp_fd >= 0, "bpf_raw_tracepoint_writable open",
		  "erroneously succeeded\n"))
		goto out_bpffd;

	close(tp_fd);
out_bpffd:
	close(bpf_fd);
}