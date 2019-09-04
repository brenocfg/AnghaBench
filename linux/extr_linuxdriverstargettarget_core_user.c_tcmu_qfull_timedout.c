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
struct timer_list {int dummy; } ;
struct tcmu_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct tcmu_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfull_timer ; 
 int /*<<< orphan*/  tcmu_device_timedout (struct tcmu_dev*) ; 
 struct tcmu_dev* udev ; 

__attribute__((used)) static void tcmu_qfull_timedout(struct timer_list *t)
{
	struct tcmu_dev *udev = from_timer(udev, t, qfull_timer);

	pr_debug("%s qfull timeout has expired\n", udev->name);
	tcmu_device_timedout(udev);
}