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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  timer_set; scalar_t__ timer_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_scu_keepalive () ; 
 int /*<<< orphan*/  intel_scu_set_heartbeat (int /*<<< orphan*/ ) ; 
 TYPE_1__ watchdog_device ; 

__attribute__((used)) static ssize_t intel_scu_write(struct file *file,
			      char const *data,
			      size_t len,
			      loff_t *ppos)
{

	if (watchdog_device.timer_started)
		/* Watchdog already started, keep it alive */
		intel_scu_keepalive();
	else
		/* Start watchdog with timer value set by init */
		intel_scu_set_heartbeat(watchdog_device.timer_set);

	return len;
}