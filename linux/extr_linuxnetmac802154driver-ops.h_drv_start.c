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
struct ieee802154_local {int started; int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* start ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_802154_drv_return_int (struct ieee802154_local*,int) ; 
 int /*<<< orphan*/  trace_802154_drv_start (struct ieee802154_local*) ; 

__attribute__((used)) static inline int drv_start(struct ieee802154_local *local)
{
	int ret;

	might_sleep();

	trace_802154_drv_start(local);
	local->started = true;
	smp_mb();
	ret = local->ops->start(&local->hw);
	trace_802154_drv_return_int(local, ret);
	return ret;
}