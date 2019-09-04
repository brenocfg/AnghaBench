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
struct twl6040 {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int TWL6040_CACHEREGNUM ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 scalar_t__ twl6040_can_write_to_chip (struct snd_soc_component*,unsigned int) ; 
 int twl6040_reg_write (struct twl6040*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  twl6040_update_dl12_cache (struct snd_soc_component*,unsigned int,unsigned int) ; 

__attribute__((used)) static int twl6040_write(struct snd_soc_component *component,
			unsigned int reg, unsigned int value)
{
	struct twl6040 *twl6040 = to_twl6040(component);

	if (reg >= TWL6040_CACHEREGNUM)
		return -EIO;

	twl6040_update_dl12_cache(component, reg, value);
	if (twl6040_can_write_to_chip(component, reg))
		return twl6040_reg_write(twl6040, reg, value);
	else
		return 0;
}