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
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 int EACCES ; 
 int MAX_BPF_STACK ; 
 struct bpf_reg_state* reg_state (struct bpf_verifier_env*,int /*<<< orphan*/ ) ; 
 scalar_t__ tnum_is_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int __check_stack_boundary(struct bpf_verifier_env *env, u32 regno,
				  int off, int access_size,
				  bool zero_size_allowed)
{
	struct bpf_reg_state *reg = reg_state(env, regno);

	if (off >= 0 || off < -MAX_BPF_STACK || off + access_size > 0 ||
	    access_size < 0 || (access_size == 0 && !zero_size_allowed)) {
		if (tnum_is_const(reg->var_off)) {
			verbose(env, "invalid stack type R%d off=%d access_size=%d\n",
				regno, off, access_size);
		} else {
			char tn_buf[48];

			tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
			verbose(env, "invalid stack type R%d var_off=%s access_size=%d\n",
				regno, tn_buf, access_size);
		}
		return -EACCES;
	}
	return 0;
}