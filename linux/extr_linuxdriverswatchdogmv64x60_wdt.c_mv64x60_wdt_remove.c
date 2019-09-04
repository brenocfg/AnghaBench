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
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv64x60_wdt_handler_disable () ; 
 int /*<<< orphan*/  mv64x60_wdt_miscdev ; 

__attribute__((used)) static int mv64x60_wdt_remove(struct platform_device *dev)
{
	misc_deregister(&mv64x60_wdt_miscdev);

	mv64x60_wdt_handler_disable();

	return 0;
}