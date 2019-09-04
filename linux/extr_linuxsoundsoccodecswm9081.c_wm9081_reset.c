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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM9081_SOFTWARE_RESET ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9081_reset(struct regmap *map)
{
	return regmap_write(map, WM9081_SOFTWARE_RESET, 0x9081);
}