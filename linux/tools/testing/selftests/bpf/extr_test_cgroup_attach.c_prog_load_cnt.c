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
struct bpf_insn {int dummy; } ;
struct bpf_cgroup_storage_key {int dummy; } ;
typedef  int /*<<< orphan*/  prog ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ADD ; 
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int BPF_CALL ; 
 int BPF_DW ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_FUNC_get_local_storage ; 
 int /*<<< orphan*/  BPF_FUNC_map_lookup_elem ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_JMP ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_LDX_MEM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_LD_MAP_FD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_CGROUP_STORAGE ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE ; 
 struct bpf_insn BPF_MOV32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_MOV64_IMM (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_CGROUP_SKB ; 
 struct bpf_insn BPF_RAW_INSN (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_10 ; 
 int /*<<< orphan*/  BPF_REG_2 ; 
 int /*<<< orphan*/  BPF_REG_3 ; 
 int BPF_STX ; 
 struct bpf_insn BPF_STX_MEM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int BPF_W ; 
 int BPF_XADD ; 
 void* bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_load_program (int /*<<< orphan*/ ,struct bpf_insn*,size_t,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ map_fd ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prog_load_cnt(int verdict, int val)
{
	int cgroup_storage_fd, percpu_cgroup_storage_fd;

	if (map_fd < 0)
		map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 8, 1, 0);
	if (map_fd < 0) {
		printf("failed to create map '%s'\n", strerror(errno));
		return -1;
	}

	cgroup_storage_fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_STORAGE,
				sizeof(struct bpf_cgroup_storage_key), 8, 0, 0);
	if (cgroup_storage_fd < 0) {
		printf("failed to create map '%s'\n", strerror(errno));
		return -1;
	}

	percpu_cgroup_storage_fd = bpf_create_map(
		BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE,
		sizeof(struct bpf_cgroup_storage_key), 8, 0, 0);
	if (percpu_cgroup_storage_fd < 0) {
		printf("failed to create map '%s'\n", strerror(errno));
		return -1;
	}

	struct bpf_insn prog[] = {
		BPF_MOV32_IMM(BPF_REG_0, 0),
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), /* *(u32 *)(fp - 4) = r0 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), /* r2 = fp - 4 */
		BPF_LD_MAP_FD(BPF_REG_1, map_fd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
		BPF_MOV64_IMM(BPF_REG_1, val), /* r1 = 1 */
		BPF_RAW_INSN(BPF_STX | BPF_XADD | BPF_DW, BPF_REG_0, BPF_REG_1, 0, 0), /* xadd r0 += r1 */

		BPF_LD_MAP_FD(BPF_REG_1, cgroup_storage_fd),
		BPF_MOV64_IMM(BPF_REG_2, 0),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_local_storage),
		BPF_MOV64_IMM(BPF_REG_1, val),
		BPF_RAW_INSN(BPF_STX | BPF_XADD | BPF_W, BPF_REG_0, BPF_REG_1, 0, 0),

		BPF_LD_MAP_FD(BPF_REG_1, percpu_cgroup_storage_fd),
		BPF_MOV64_IMM(BPF_REG_2, 0),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_local_storage),
		BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 0x1),
		BPF_STX_MEM(BPF_W, BPF_REG_0, BPF_REG_3, 0),

		BPF_MOV64_IMM(BPF_REG_0, verdict), /* r0 = verdict */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = sizeof(prog) / sizeof(struct bpf_insn);
	int ret;

	ret = bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
			       prog, insns_cnt, "GPL", 0,
			       bpf_log_buf, BPF_LOG_BUF_SIZE);

	if (ret < 0) {
		log_err("Loading program");
		printf("Output from verifier:\n%s\n-------\n", bpf_log_buf);
		return 0;
	}
	close(cgroup_storage_fd);
	return ret;
}