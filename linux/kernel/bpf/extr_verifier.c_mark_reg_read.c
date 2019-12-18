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
typedef  int u8 ;
struct bpf_verifier_env {int longest_mark_read_walk; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct bpf_reg_state {int live; size_t type; struct bpf_reg_state* parent; int /*<<< orphan*/  off; TYPE_1__ var_off; } ;

/* Variables and functions */
 int EFAULT ; 
 int REG_LIVE_DONE ; 
 int REG_LIVE_READ ; 
 int REG_LIVE_READ32 ; 
 int REG_LIVE_READ64 ; 
 int REG_LIVE_WRITTEN ; 
 int /*<<< orphan*/ * reg_type_str ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mark_reg_read(struct bpf_verifier_env *env,
			 const struct bpf_reg_state *state,
			 struct bpf_reg_state *parent, u8 flag)
{
	bool writes = parent == state->parent; /* Observe write marks */
	int cnt = 0;

	while (parent) {
		/* if read wasn't screened by an earlier write ... */
		if (writes && state->live & REG_LIVE_WRITTEN)
			break;
		if (parent->live & REG_LIVE_DONE) {
			verbose(env, "verifier BUG type %s var_off %lld off %d\n",
				reg_type_str[parent->type],
				parent->var_off.value, parent->off);
			return -EFAULT;
		}
		/* The first condition is more likely to be true than the
		 * second, checked it first.
		 */
		if ((parent->live & REG_LIVE_READ) == flag ||
		    parent->live & REG_LIVE_READ64)
			/* The parentage chain never changes and
			 * this parent was already marked as LIVE_READ.
			 * There is no need to keep walking the chain again and
			 * keep re-marking all parents as LIVE_READ.
			 * This case happens when the same register is read
			 * multiple times without writes into it in-between.
			 * Also, if parent has the stronger REG_LIVE_READ64 set,
			 * then no need to set the weak REG_LIVE_READ32.
			 */
			break;
		/* ... then we depend on parent's value */
		parent->live |= flag;
		/* REG_LIVE_READ64 overrides REG_LIVE_READ32. */
		if (flag == REG_LIVE_READ64)
			parent->live &= ~REG_LIVE_READ32;
		state = parent;
		parent = state->parent;
		writes = true;
		cnt++;
	}

	if (env->longest_mark_read_walk < cnt)
		env->longest_mark_read_walk = cnt;
	return 0;
}