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
struct wireless_dev {int dummy; } ;
struct vif_params {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {struct wireless_dev* (* add_virtual_intf ) (int /*<<< orphan*/ *,char*,unsigned char,int,struct vif_params*) ;} ;

/* Variables and functions */
 struct wireless_dev* stub1 (int /*<<< orphan*/ *,char*,unsigned char,int,struct vif_params*) ; 
 int /*<<< orphan*/  trace_rdev_add_virtual_intf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  trace_rdev_return_wdev (int /*<<< orphan*/ *,struct wireless_dev*) ; 

__attribute__((used)) static inline struct wireless_dev
*rdev_add_virtual_intf(struct cfg80211_registered_device *rdev, char *name,
		       unsigned char name_assign_type,
		       enum nl80211_iftype type,
		       struct vif_params *params)
{
	struct wireless_dev *ret;
	trace_rdev_add_virtual_intf(&rdev->wiphy, name, type);
	ret = rdev->ops->add_virtual_intf(&rdev->wiphy, name, name_assign_type,
					  type, params);
	trace_rdev_return_wdev(&rdev->wiphy, ret);
	return ret;
}