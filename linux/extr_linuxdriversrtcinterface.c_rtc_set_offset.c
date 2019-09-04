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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ dev; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_offset ) (int /*<<< orphan*/ ,long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  trace_rtc_set_offset (long,int) ; 

int rtc_set_offset(struct rtc_device *rtc, long offset)
{
	int ret;

	if (!rtc->ops)
		return -ENODEV;

	if (!rtc->ops->set_offset)
		return -EINVAL;

	mutex_lock(&rtc->ops_lock);
	ret = rtc->ops->set_offset(rtc->dev.parent, offset);
	mutex_unlock(&rtc->ops_lock);

	trace_rtc_set_offset(offset, ret);
	return ret;
}