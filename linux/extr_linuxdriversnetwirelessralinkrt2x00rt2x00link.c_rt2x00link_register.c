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
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  watchdog_work; } ;
struct rt2x00_dev {TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00link_tuner ; 
 int /*<<< orphan*/  rt2x00link_watchdog ; 

void rt2x00link_register(struct rt2x00_dev *rt2x00dev)
{
	INIT_DELAYED_WORK(&rt2x00dev->link.watchdog_work, rt2x00link_watchdog);
	INIT_DELAYED_WORK(&rt2x00dev->link.work, rt2x00link_tuner);
}