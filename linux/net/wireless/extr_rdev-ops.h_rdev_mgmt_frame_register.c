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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mgmt_frame_register ) (int /*<<< orphan*/ *,struct wireless_dev*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct wireless_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rdev_mgmt_frame_register (int /*<<< orphan*/ *,struct wireless_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rdev_return_void (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
rdev_mgmt_frame_register(struct cfg80211_registered_device *rdev,
			 struct wireless_dev *wdev, u16 frame_type, bool reg)
{
	might_sleep();

	trace_rdev_mgmt_frame_register(&rdev->wiphy, wdev , frame_type, reg);
	rdev->ops->mgmt_frame_register(&rdev->wiphy, wdev , frame_type, reg);
	trace_rdev_return_void(&rdev->wiphy);
}