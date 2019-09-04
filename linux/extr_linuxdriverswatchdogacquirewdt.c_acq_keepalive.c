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

/* Variables and functions */
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_start ; 

__attribute__((used)) static void acq_keepalive(void)
{
	/* Write a watchdog value */
	inb_p(wdt_start);
}