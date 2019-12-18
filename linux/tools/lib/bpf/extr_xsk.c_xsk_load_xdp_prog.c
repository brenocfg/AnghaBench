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
struct TYPE_2__ {int /*<<< orphan*/  xdp_flags; } ;
struct xsk_socket {int prog_fd; TYPE_1__ config; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  xsks_map_fd; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  prog ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ADD ; 
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_EMIT_CALL (int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_FUNC_map_lookup_elem ; 
 int /*<<< orphan*/  BPF_FUNC_redirect_map ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_LDX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_LD_MAP_FD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_MOV32_IMM (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_10 ; 
 int /*<<< orphan*/  BPF_REG_2 ; 
 int /*<<< orphan*/  BPF_REG_3 ; 
 struct bpf_insn BPF_STX_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_W ; 
 int bpf_load_program (int /*<<< orphan*/ ,struct bpf_insn*,size_t,char*,int /*<<< orphan*/ ,char*,int const) ; 
 int bpf_set_link_xdp_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 

__attribute__((used)) static int xsk_load_xdp_prog(struct xsk_socket *xsk)
{
	static const int log_buf_size = 16 * 1024;
	char log_buf[log_buf_size];
	int err, prog_fd;

	/* This is the C-program:
	 * SEC("xdp_sock") int xdp_sock_prog(struct xdp_md *ctx)
	 * {
	 *     int index = ctx->rx_queue_index;
	 *
	 *     // A set entry here means that the correspnding queue_id
	 *     // has an active AF_XDP socket bound to it.
	 *     if (bpf_map_lookup_elem(&xsks_map, &index))
	 *         return bpf_redirect_map(&xsks_map, index, 0);
	 *
	 *     return XDP_PASS;
	 * }
	 */
	struct bpf_insn prog[] = {
		/* r1 = *(u32 *)(r1 + 16) */
		BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_1, 16),
		/* *(u32 *)(r10 - 4) = r1 */
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_1, -4),
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4),
		BPF_LD_MAP_FD(BPF_REG_1, xsk->xsks_map_fd),
		BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
		BPF_MOV32_IMM(BPF_REG_0, 2),
		/* if r1 == 0 goto +5 */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 5),
		/* r2 = *(u32 *)(r10 - 4) */
		BPF_LD_MAP_FD(BPF_REG_1, xsk->xsks_map_fd),
		BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_10, -4),
		BPF_MOV32_IMM(BPF_REG_3, 0),
		BPF_EMIT_CALL(BPF_FUNC_redirect_map),
		/* The jumps are to this instruction */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = sizeof(prog) / sizeof(struct bpf_insn);

	prog_fd = bpf_load_program(BPF_PROG_TYPE_XDP, prog, insns_cnt,
				   "LGPL-2.1 or BSD-2-Clause", 0, log_buf,
				   log_buf_size);
	if (prog_fd < 0) {
		pr_warning("BPF log buffer:\n%s", log_buf);
		return prog_fd;
	}

	err = bpf_set_link_xdp_fd(xsk->ifindex, prog_fd, xsk->config.xdp_flags);
	if (err) {
		close(prog_fd);
		return err;
	}

	xsk->prog_fd = prog_fd;
	return 0;
}