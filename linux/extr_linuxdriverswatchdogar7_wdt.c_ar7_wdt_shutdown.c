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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar7_wdt_disable_wdt () ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static void ar7_wdt_shutdown(struct platform_device *pdev)
{
	if (!nowayout)
		ar7_wdt_disable_wdt();
}