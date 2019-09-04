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
struct watchdog_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pretimeout_noop(struct watchdog_device *wdd)
{
	pr_alert("watchdog%d: pretimeout event\n", wdd->id);
}