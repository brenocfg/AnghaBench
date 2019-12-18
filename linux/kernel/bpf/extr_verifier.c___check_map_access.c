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
typedef  size_t u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {struct bpf_map* map_ptr; } ;
struct bpf_map {int value_size; } ;

/* Variables and functions */
 int EACCES ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int,int,int) ; 

__attribute__((used)) static int __check_map_access(struct bpf_verifier_env *env, u32 regno, int off,
			      int size, bool zero_size_allowed)
{
	struct bpf_reg_state *regs = cur_regs(env);
	struct bpf_map *map = regs[regno].map_ptr;

	if (off < 0 || size < 0 || (size == 0 && !zero_size_allowed) ||
	    off + size > map->value_size) {
		verbose(env, "invalid access to map value, value_size=%d off=%d size=%d\n",
			map->value_size, off, size);
		return -EACCES;
	}
	return 0;
}