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
 int /*<<< orphan*/  SBC7240_ENABLED_STATUS_BIT ; 
 int /*<<< orphan*/  SBC7240_ENABLE_PORT ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static inline void wdt_keepalive(void)
{
	if (test_bit(SBC7240_ENABLED_STATUS_BIT, &wdt_status))
		inb_p(SBC7240_ENABLE_PORT);
}