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
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  PET_ADDR ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ebc_c384_wdt_start(struct watchdog_device *wdev)
{
	unsigned t = wdev->timeout;

	/* resolution is in minutes for timeouts greater than 255 seconds */
	if (t > 255)
		t = DIV_ROUND_UP(t, 60);

	outb(t, PET_ADDR);

	return 0;
}