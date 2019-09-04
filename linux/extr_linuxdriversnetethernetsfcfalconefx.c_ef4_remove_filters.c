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
struct ef4_nic {int /*<<< orphan*/  filter_sem; TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* filter_table_remove ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ef4_remove_filters(struct ef4_nic *efx)
{
#ifdef CONFIG_RFS_ACCEL
	struct ef4_channel *channel;

	ef4_for_each_channel(channel, efx)
		kfree(channel->rps_flow_id);
#endif
	down_write(&efx->filter_sem);
	efx->type->filter_table_remove(efx);
	up_write(&efx->filter_sem);
}