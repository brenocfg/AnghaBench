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
struct ieee802154_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int (* set_frame_retries ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_drv_return_int (struct ieee802154_local*,int) ; 
 int /*<<< orphan*/  trace_802154_drv_set_max_frame_retries (struct ieee802154_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
drv_set_max_frame_retries(struct ieee802154_local *local, s8 max_frame_retries)
{
	int ret;

	might_sleep();

	if (!local->ops->set_frame_retries) {
		WARN_ON(1);
		return -EOPNOTSUPP;
	}

	trace_802154_drv_set_max_frame_retries(local, max_frame_retries);
	ret = local->ops->set_frame_retries(&local->hw, max_frame_retries);
	trace_802154_drv_return_int(local, ret);
	return ret;
}