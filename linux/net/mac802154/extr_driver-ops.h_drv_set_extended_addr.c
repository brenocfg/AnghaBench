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
struct ieee802154_hw_addr_filt {int /*<<< orphan*/  ieee_addr; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int (* set_hw_addr_filt ) (int /*<<< orphan*/ *,struct ieee802154_hw_addr_filt*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE802154_AFILT_IEEEADDR_CHANGED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,struct ieee802154_hw_addr_filt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_drv_return_int (struct ieee802154_local*,int) ; 
 int /*<<< orphan*/  trace_802154_drv_set_extended_addr (struct ieee802154_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
drv_set_extended_addr(struct ieee802154_local *local, __le64 extended_addr)
{
	struct ieee802154_hw_addr_filt filt;
	int ret;

	might_sleep();

	if (!local->ops->set_hw_addr_filt) {
		WARN_ON(1);
		return -EOPNOTSUPP;
	}

	filt.ieee_addr = extended_addr;

	trace_802154_drv_set_extended_addr(local, extended_addr);
	ret = local->ops->set_hw_addr_filt(&local->hw, &filt,
					    IEEE802154_AFILT_IEEEADDR_CHANGED);
	trace_802154_drv_return_int(local, ret);
	return ret;
}