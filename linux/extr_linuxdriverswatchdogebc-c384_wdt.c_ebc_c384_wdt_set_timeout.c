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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_ADDR ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 unsigned int roundup (unsigned int,int) ; 

__attribute__((used)) static int ebc_c384_wdt_set_timeout(struct watchdog_device *wdev, unsigned t)
{
	/* resolution is in minutes for timeouts greater than 255 seconds */
	if (t > 255) {
		/* round second resolution up to minute granularity */
		wdev->timeout = roundup(t, 60);

		/* set watchdog timer for minutes */
		outb(0x00, CFG_ADDR);
	} else {
		wdev->timeout = t;

		/* set watchdog timer for seconds */
		outb(0x80, CFG_ADDR);
	}

	return 0;
}