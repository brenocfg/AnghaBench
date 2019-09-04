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
typedef  int /*<<< orphan*/  tn_buf ;
struct tnum {int dummy; } ;
struct bpf_verifier_env {TYPE_1__* prog; } ;
struct bpf_reg_state {size_t type; int /*<<< orphan*/  var_off; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  BPF_PROG_TYPE_CGROUP_DEVICE 132 
#define  BPF_PROG_TYPE_CGROUP_SKB 131 
#define  BPF_PROG_TYPE_CGROUP_SOCK 130 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 129 
#define  BPF_PROG_TYPE_SOCK_OPS 128 
 int BPF_REG_0 ; 
 int EINVAL ; 
 size_t SCALAR_VALUE ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/ * reg_type_str ; 
 int /*<<< orphan*/  tnum_in (struct tnum,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_is_unknown (int /*<<< orphan*/ ) ; 
 struct tnum tnum_range (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_return_code(struct bpf_verifier_env *env)
{
	struct bpf_reg_state *reg;
	struct tnum range = tnum_range(0, 1);

	switch (env->prog->type) {
	case BPF_PROG_TYPE_CGROUP_SKB:
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	case BPF_PROG_TYPE_SOCK_OPS:
	case BPF_PROG_TYPE_CGROUP_DEVICE:
		break;
	default:
		return 0;
	}

	reg = cur_regs(env) + BPF_REG_0;
	if (reg->type != SCALAR_VALUE) {
		verbose(env, "At program exit the register R0 is not a known value (%s)\n",
			reg_type_str[reg->type]);
		return -EINVAL;
	}

	if (!tnum_in(range, reg->var_off)) {
		verbose(env, "At program exit the register R0 ");
		if (!tnum_is_unknown(reg->var_off)) {
			char tn_buf[48];

			tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
			verbose(env, "has value %s", tn_buf);
		} else {
			verbose(env, "has unknown scalar value");
		}
		verbose(env, " should have been 0 or 1\n");
		return -EINVAL;
	}
	return 0;
}