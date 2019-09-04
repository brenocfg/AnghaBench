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
struct intel_sst_drv {int sst_state; int /*<<< orphan*/  sst_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void sst_set_fw_state_locked(
		struct intel_sst_drv *sst_drv_ctx, int sst_state)
{
	mutex_lock(&sst_drv_ctx->sst_lock);
	sst_drv_ctx->sst_state = sst_state;
	mutex_unlock(&sst_drv_ctx->sst_lock);
}