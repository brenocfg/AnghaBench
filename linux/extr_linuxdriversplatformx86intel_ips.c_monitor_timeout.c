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
struct ips_driver {int /*<<< orphan*/  monitor; } ;

/* Variables and functions */
 struct ips_driver* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ips_driver* ips ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void monitor_timeout(struct timer_list *t)
{
	struct ips_driver *ips = from_timer(ips, t, timer);
	wake_up_process(ips->monitor);
}