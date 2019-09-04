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
 int /*<<< orphan*/  map ; 
 int /*<<< orphan*/  mask ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  offset ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value ; 

__attribute__((used)) static void syscon_poweroff(void)
{
	/* Issue the poweroff */
	regmap_update_bits(map, offset, mask, value);

	mdelay(1000);

	pr_emerg("Unable to poweroff system\n");
}