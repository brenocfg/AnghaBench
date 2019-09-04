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
struct pinctrl_map {int dummy; } ;

/* Variables and functions */
 int pinctrl_register_map (struct pinctrl_map const*,unsigned int,int) ; 

int pinctrl_register_mappings(const struct pinctrl_map *maps,
			      unsigned num_maps)
{
	return pinctrl_register_map(maps, num_maps, true);
}