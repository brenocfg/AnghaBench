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
struct watchdog_device {int dummy; } ;
struct pic32_dmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmt_enable (struct pic32_dmt*) ; 
 int dmt_keepalive (struct pic32_dmt*) ; 
 struct pic32_dmt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int pic32_dmt_start(struct watchdog_device *wdd)
{
	struct pic32_dmt *dmt = watchdog_get_drvdata(wdd);

	dmt_enable(dmt);
	return dmt_keepalive(dmt);
}