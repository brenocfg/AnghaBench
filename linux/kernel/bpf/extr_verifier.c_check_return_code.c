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
struct bpf_reg_state {size_t type; struct tnum var_off; } ;
struct TYPE_2__ {int type; int enforce_expected_attach_type; int /*<<< orphan*/  expected_attach_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_INET_EGRESS ; 
 int /*<<< orphan*/  BPF_CGROUP_UDP4_RECVMSG ; 
 int /*<<< orphan*/  BPF_CGROUP_UDP6_RECVMSG ; 
#define  BPF_PROG_TYPE_CGROUP_DEVICE 134 
#define  BPF_PROG_TYPE_CGROUP_SKB 133 
#define  BPF_PROG_TYPE_CGROUP_SOCK 132 
#define  BPF_PROG_TYPE_CGROUP_SOCKOPT 131 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 130 
#define  BPF_PROG_TYPE_CGROUP_SYSCTL 129 
#define  BPF_PROG_TYPE_SOCK_OPS 128 
 int BPF_REG_0 ; 
 int EINVAL ; 
 size_t SCALAR_VALUE ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 char** reg_type_str ; 
 scalar_t__ tnum_in (struct tnum,struct tnum) ; 
 int /*<<< orphan*/  tnum_is_unknown (struct tnum) ; 
 struct tnum tnum_range (int,int) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,struct tnum) ; 
 struct tnum tnum_unknown ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_return_code(struct bpf_verifier_env *env)
{
	struct tnum enforce_attach_type_range = tnum_unknown;
	struct bpf_reg_state *reg;
	struct tnum range = tnum_range(0, 1);

	switch (env->prog->type) {
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		if (env->prog->expected_attach_type == BPF_CGROUP_UDP4_RECVMSG ||
		    env->prog->expected_attach_type == BPF_CGROUP_UDP6_RECVMSG)
			range = tnum_range(1, 1);
		break;
	case BPF_PROG_TYPE_CGROUP_SKB:
		if (env->prog->expected_attach_type == BPF_CGROUP_INET_EGRESS) {
			range = tnum_range(0, 3);
			enforce_attach_type_range = tnum_range(2, 3);
		}
		break;
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_SOCK_OPS:
	case BPF_PROG_TYPE_CGROUP_DEVICE:
	case BPF_PROG_TYPE_CGROUP_SYSCTL:
	case BPF_PROG_TYPE_CGROUP_SOCKOPT:
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
		char tn_buf[48];

		verbose(env, "At program exit the register R0 ");
		if (!tnum_is_unknown(reg->var_off)) {
			tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
			verbose(env, "has value %s", tn_buf);
		} else {
			verbose(env, "has unknown scalar value");
		}
		tnum_strn(tn_buf, sizeof(tn_buf), range);
		verbose(env, " should have been in %s\n", tn_buf);
		return -EINVAL;
	}

	if (!tnum_is_unknown(enforce_attach_type_range) &&
	    tnum_in(enforce_attach_type_range, reg->var_off))
		env->prog->enforce_expected_attach_type = 1;
	return 0;
}