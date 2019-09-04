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
struct tee_shm {int dummy; } ;
struct tee_device {int dummy; } ;
struct tee_context {struct tee_device* teedev; } ;
struct optee_rpc_param {int /*<<< orphan*/  a0; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a5; int /*<<< orphan*/  a4; } ;
struct optee_call_ctx {int dummy; } ;
struct optee {int dummy; } ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct tee_shm*) ; 
 int /*<<< orphan*/  OPTEE_SMC_CALL_RETURN_FROM_RPC ; 
 int OPTEE_SMC_RETURN_GET_RPC_FUNC (int /*<<< orphan*/ ) ; 
#define  OPTEE_SMC_RPC_FUNC_ALLOC 131 
#define  OPTEE_SMC_RPC_FUNC_CMD 130 
#define  OPTEE_SMC_RPC_FUNC_FOREIGN_INTR 129 
#define  OPTEE_SMC_RPC_FUNC_FREE 128 
 int /*<<< orphan*/  TEE_SHM_MAPPED ; 
 int /*<<< orphan*/  handle_rpc_func_cmd (struct tee_context*,struct optee*,struct tee_shm*,struct optee_call_ctx*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_pair_from_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 struct tee_shm* reg_pair_to_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct optee* tee_get_drvdata (struct tee_device*) ; 
 struct tee_shm* tee_shm_alloc (struct tee_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_shm_free (struct tee_shm*) ; 
 int /*<<< orphan*/  tee_shm_get_pa (struct tee_shm*,int /*<<< orphan*/ ,unsigned long*) ; 

void optee_handle_rpc(struct tee_context *ctx, struct optee_rpc_param *param,
		      struct optee_call_ctx *call_ctx)
{
	struct tee_device *teedev = ctx->teedev;
	struct optee *optee = tee_get_drvdata(teedev);
	struct tee_shm *shm;
	phys_addr_t pa;

	switch (OPTEE_SMC_RETURN_GET_RPC_FUNC(param->a0)) {
	case OPTEE_SMC_RPC_FUNC_ALLOC:
		shm = tee_shm_alloc(ctx, param->a1, TEE_SHM_MAPPED);
		if (!IS_ERR(shm) && !tee_shm_get_pa(shm, 0, &pa)) {
			reg_pair_from_64(&param->a1, &param->a2, pa);
			reg_pair_from_64(&param->a4, &param->a5,
					 (unsigned long)shm);
		} else {
			param->a1 = 0;
			param->a2 = 0;
			param->a4 = 0;
			param->a5 = 0;
		}
		break;
	case OPTEE_SMC_RPC_FUNC_FREE:
		shm = reg_pair_to_ptr(param->a1, param->a2);
		tee_shm_free(shm);
		break;
	case OPTEE_SMC_RPC_FUNC_FOREIGN_INTR:
		/*
		 * A foreign interrupt was raised while secure world was
		 * executing, since they are handled in Linux a dummy RPC is
		 * performed to let Linux take the interrupt through the normal
		 * vector.
		 */
		break;
	case OPTEE_SMC_RPC_FUNC_CMD:
		shm = reg_pair_to_ptr(param->a1, param->a2);
		handle_rpc_func_cmd(ctx, optee, shm, call_ctx);
		break;
	default:
		pr_warn("Unknown RPC func 0x%x\n",
			(u32)OPTEE_SMC_RETURN_GET_RPC_FUNC(param->a0));
		break;
	}

	param->a0 = OPTEE_SMC_CALL_RETURN_FROM_RPC;
}