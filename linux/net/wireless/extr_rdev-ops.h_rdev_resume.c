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
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* resume ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_resume(struct cfg80211_registered_device *rdev)
{
	int ret;
	trace_rdev_resume(&rdev->wiphy);
	ret = rdev->ops->resume(&rdev->wiphy);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}