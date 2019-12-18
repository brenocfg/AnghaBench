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
typedef  int /*<<< orphan*/  u64 ;
struct bpf_verifier_state {scalar_t__ active_spin_lock; } ;
struct bpf_verifier_env {struct bpf_verifier_state* cur_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct bpf_reg_state {scalar_t__ type; scalar_t__ id; int /*<<< orphan*/  off; TYPE_1__ var_off; struct bpf_map* map_ptr; } ;
struct bpf_map {int /*<<< orphan*/  spin_lock_off; int /*<<< orphan*/  name; int /*<<< orphan*/  btf; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ PTR_TO_MAP_VALUE ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  map_value_has_spin_lock (struct bpf_map*) ; 
 int tnum_is_const (TYPE_1__) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int process_spin_lock(struct bpf_verifier_env *env, int regno,
			     bool is_lock)
{
	struct bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];
	struct bpf_verifier_state *cur = env->cur_state;
	bool is_const = tnum_is_const(reg->var_off);
	struct bpf_map *map = reg->map_ptr;
	u64 val = reg->var_off.value;

	if (reg->type != PTR_TO_MAP_VALUE) {
		verbose(env, "R%d is not a pointer to map_value\n", regno);
		return -EINVAL;
	}
	if (!is_const) {
		verbose(env,
			"R%d doesn't have constant offset. bpf_spin_lock has to be at the constant offset\n",
			regno);
		return -EINVAL;
	}
	if (!map->btf) {
		verbose(env,
			"map '%s' has to have BTF in order to use bpf_spin_lock\n",
			map->name);
		return -EINVAL;
	}
	if (!map_value_has_spin_lock(map)) {
		if (map->spin_lock_off == -E2BIG)
			verbose(env,
				"map '%s' has more than one 'struct bpf_spin_lock'\n",
				map->name);
		else if (map->spin_lock_off == -ENOENT)
			verbose(env,
				"map '%s' doesn't have 'struct bpf_spin_lock'\n",
				map->name);
		else
			verbose(env,
				"map '%s' is not a struct type or bpf_spin_lock is mangled\n",
				map->name);
		return -EINVAL;
	}
	if (map->spin_lock_off != val + reg->off) {
		verbose(env, "off %lld doesn't point to 'struct bpf_spin_lock'\n",
			val + reg->off);
		return -EINVAL;
	}
	if (is_lock) {
		if (cur->active_spin_lock) {
			verbose(env,
				"Locking two bpf_spin_locks are not allowed\n");
			return -EINVAL;
		}
		cur->active_spin_lock = reg->id;
	} else {
		if (!cur->active_spin_lock) {
			verbose(env, "bpf_spin_unlock without taking a lock\n");
			return -EINVAL;
		}
		if (cur->active_spin_lock != reg->id) {
			verbose(env, "bpf_spin_unlock of different lock\n");
			return -EINVAL;
		}
		cur->active_spin_lock = 0;
	}
	return 0;
}