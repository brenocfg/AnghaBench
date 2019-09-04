#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {TYPE_4__* prog; TYPE_2__* insn_aux_data; TYPE_1__* ops; } ;
struct bpf_insn_access_aux {int reg_type; int /*<<< orphan*/  ctx_field_size; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;
struct TYPE_8__ {TYPE_3__* aux; } ;
struct TYPE_7__ {int max_ctx_offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx_field_size; } ;
struct TYPE_5__ {scalar_t__ (* is_valid_access ) (int,int,int,TYPE_4__*,struct bpf_insn_access_aux*) ;} ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ stub1 (int,int,int,TYPE_4__*,struct bpf_insn_access_aux*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int,int) ; 

__attribute__((used)) static int check_ctx_access(struct bpf_verifier_env *env, int insn_idx, int off, int size,
			    enum bpf_access_type t, enum bpf_reg_type *reg_type)
{
	struct bpf_insn_access_aux info = {
		.reg_type = *reg_type,
	};

	if (env->ops->is_valid_access &&
	    env->ops->is_valid_access(off, size, t, env->prog, &info)) {
		/* A non zero info.ctx_field_size indicates that this field is a
		 * candidate for later verifier transformation to load the whole
		 * field and then apply a mask when accessed with a narrower
		 * access than actual ctx access size. A zero info.ctx_field_size
		 * will only allow for whole field access and rejects any other
		 * type of narrower access.
		 */
		*reg_type = info.reg_type;

		env->insn_aux_data[insn_idx].ctx_field_size = info.ctx_field_size;
		/* remember the offset of last byte accessed in ctx */
		if (env->prog->aux->max_ctx_offset < off + size)
			env->prog->aux->max_ctx_offset = off + size;
		return 0;
	}

	verbose(env, "invalid bpf_context access off=%d size=%d\n", off, size);
	return -EACCES;
}