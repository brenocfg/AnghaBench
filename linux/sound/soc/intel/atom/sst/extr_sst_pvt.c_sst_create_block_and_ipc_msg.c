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
struct sst_block {int dummy; } ;
struct ipc_post {int dummy; } ;
struct intel_sst_drv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (struct ipc_post*) ; 
 struct sst_block* sst_create_block (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_create_ipc_msg (struct ipc_post**,int) ; 

int sst_create_block_and_ipc_msg(struct ipc_post **arg, bool large,
		struct intel_sst_drv *sst_drv_ctx, struct sst_block **block,
		u32 msg_id, u32 drv_id)
{
	int retval = 0;

	retval = sst_create_ipc_msg(arg, large);
	if (retval)
		return retval;
	*block = sst_create_block(sst_drv_ctx, msg_id, drv_id);
	if (*block == NULL) {
		kfree(*arg);
		return -ENOMEM;
	}
	return retval;
}