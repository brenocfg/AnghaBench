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
struct mrst_rtc {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mrst_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_mrst_do_shutdown () ; 

__attribute__((used)) static void rtc_mrst_do_remove(struct device *dev)
{
	struct mrst_rtc	*mrst = dev_get_drvdata(dev);

	rtc_mrst_do_shutdown();

	mrst->rtc = NULL;
	mrst->dev = NULL;
}