#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_3__ {scalar_t__ value; } ;
struct bpf_reg_state {TYPE_1__ var_off; scalar_t__ off; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  tnum_is_const (TYPE_1__) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,TYPE_1__) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_ctx_reg(struct bpf_verifier_env *env,
			 const struct bpf_reg_state *reg, int regno)
{
	/* Access to ctx or passing it to a helper is only allowed in
	 * its original, unmodified form.
	 */

	if (reg->off) {
		verbose(env, "dereference of modified ctx ptr R%d off=%d disallowed\n",
			regno, reg->off);
		return -EACCES;
	}

	if (!tnum_is_const(reg->var_off) || reg->var_off.value) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
		verbose(env, "variable ctx access var_off=%s disallowed\n", tn_buf);
		return -EACCES;
	}

	return 0;
}