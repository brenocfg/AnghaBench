#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {struct bpf_insn_aux_data* insn_aux_data; } ;
struct bpf_insn_aux_data {int /*<<< orphan*/  map_state; } ;
struct bpf_call_arg_meta {TYPE_1__* map_ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpriv_array; } ;

/* Variables and functions */
 int BPF_FUNC_map_delete_elem ; 
 int BPF_FUNC_map_lookup_elem ; 
 int BPF_FUNC_map_update_elem ; 
 int BPF_FUNC_tail_call ; 
 TYPE_1__* BPF_MAP_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* BPF_MAP_PTR_POISON ; 
 int EINVAL ; 
 int /*<<< orphan*/  bpf_map_ptr_store (struct bpf_insn_aux_data*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static int
record_func_map(struct bpf_verifier_env *env, struct bpf_call_arg_meta *meta,
		int func_id, int insn_idx)
{
	struct bpf_insn_aux_data *aux = &env->insn_aux_data[insn_idx];

	if (func_id != BPF_FUNC_tail_call &&
	    func_id != BPF_FUNC_map_lookup_elem &&
	    func_id != BPF_FUNC_map_update_elem &&
	    func_id != BPF_FUNC_map_delete_elem)
		return 0;

	if (meta->map_ptr == NULL) {
		verbose(env, "kernel subsystem misconfigured verifier\n");
		return -EINVAL;
	}

	if (!BPF_MAP_PTR(aux->map_state))
		bpf_map_ptr_store(aux, meta->map_ptr,
				  meta->map_ptr->unpriv_array);
	else if (BPF_MAP_PTR(aux->map_state) != meta->map_ptr)
		bpf_map_ptr_store(aux, BPF_MAP_PTR_POISON,
				  meta->map_ptr->unpriv_array);
	return 0;
}