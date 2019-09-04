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
struct samsung_laptop {int has_stepping_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int read_brightness (struct samsung_laptop*) ; 
 int /*<<< orphan*/  set_brightness (struct samsung_laptop*,int) ; 

__attribute__((used)) static void check_for_stepping_quirk(struct samsung_laptop *samsung)
{
	int initial_level;
	int check_level;
	int orig_level = read_brightness(samsung);

	/*
	 * Some laptops exhibit the strange behaviour of stepping toward
	 * (rather than setting) the brightness except when changing to/from
	 * brightness level 0. This behaviour is checked for here and worked
	 * around in set_brightness.
	 */

	if (orig_level == 0)
		set_brightness(samsung, 1);

	initial_level = read_brightness(samsung);

	if (initial_level <= 2)
		check_level = initial_level + 2;
	else
		check_level = initial_level - 2;

	samsung->has_stepping_quirk = false;
	set_brightness(samsung, check_level);

	if (read_brightness(samsung) != check_level) {
		samsung->has_stepping_quirk = true;
		pr_info("enabled workaround for brightness stepping quirk\n");
	}

	set_brightness(samsung, orig_level);
}