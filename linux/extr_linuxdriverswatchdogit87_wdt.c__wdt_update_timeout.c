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
 scalar_t__ IT8721_ID ; 
 int /*<<< orphan*/  WDTCFG ; 
 int /*<<< orphan*/  WDTVALLSB ; 
 int /*<<< orphan*/  WDTVALMSB ; 
 unsigned char WDT_KRST ; 
 unsigned char WDT_PWROK ; 
 unsigned char WDT_TOV1 ; 
 scalar_t__ chip_type ; 
 unsigned int max_units ; 
 int /*<<< orphan*/  superio_outb (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ testmode ; 

__attribute__((used)) static void _wdt_update_timeout(unsigned int t)
{
	unsigned char cfg = WDT_KRST;

	if (testmode)
		cfg = 0;

	if (t <= max_units)
		cfg |= WDT_TOV1;
	else
		t /= 60;

	if (chip_type != IT8721_ID)
		cfg |= WDT_PWROK;

	superio_outb(cfg, WDTCFG);
	superio_outb(t, WDTVALLSB);
	if (max_units > 255)
		superio_outb(t >> 8, WDTVALMSB);
}