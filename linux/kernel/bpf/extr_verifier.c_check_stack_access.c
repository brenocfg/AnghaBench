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
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 int EACCES ; 
 int MAX_BPF_STACK ; 
 int /*<<< orphan*/  tnum_is_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_stack_access(struct bpf_verifier_env *env,
			      const struct bpf_reg_state *reg,
			      int off, int size)
{
	/* Stack accesses must be at a fixed offset, so that we
	 * can determine what type of data were returned. See
	 * check_stack_read().
	 */
	if (!tnum_is_const(reg->var_off)) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
		verbose(env, "variable stack access var_off=%s off=%d size=%d\n",
			tn_buf, off, size);
		return -EACCES;
	}

	if (off >= 0 || off < -MAX_BPF_STACK) {
		verbose(env, "invalid stack off=%d size=%d\n", off, size);
		return -EACCES;
	}

	return 0;
}