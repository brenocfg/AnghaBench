#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tee_shm {int dummy; } ;
struct TYPE_3__ {scalar_t__ c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
struct tee_param {TYPE_2__ u; int /*<<< orphan*/  attr; } ;
struct tee_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTEE_MSG_RPC_CMD_SHM_FREE ; 
 int /*<<< orphan*/  OPTEE_MSG_RPC_SHM_TYPE_APPL ; 
 int /*<<< orphan*/  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT ; 
 int /*<<< orphan*/  optee_supp_thrd_req (struct tee_context*,int /*<<< orphan*/ ,int,struct tee_param*) ; 
 int /*<<< orphan*/  tee_shm_get_id (struct tee_shm*) ; 
 int /*<<< orphan*/  tee_shm_put (struct tee_shm*) ; 

__attribute__((used)) static void cmd_free_suppl(struct tee_context *ctx, struct tee_shm *shm)
{
	struct tee_param param;

	param.attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	param.u.value.a = OPTEE_MSG_RPC_SHM_TYPE_APPL;
	param.u.value.b = tee_shm_get_id(shm);
	param.u.value.c = 0;

	/*
	 * Match the tee_shm_get_from_id() in cmd_alloc_suppl() as secure
	 * world has released its reference.
	 *
	 * It's better to do this before sending the request to supplicant
	 * as we'd like to let the process doing the initial allocation to
	 * do release the last reference too in order to avoid stacking
	 * many pending fput() on the client process. This could otherwise
	 * happen if secure world does many allocate and free in a single
	 * invoke.
	 */
	tee_shm_put(shm);

	optee_supp_thrd_req(ctx, OPTEE_MSG_RPC_CMD_SHM_FREE, 1, &param);
}