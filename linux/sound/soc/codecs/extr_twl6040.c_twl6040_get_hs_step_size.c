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
 scalar_t__ TWL6040_REV_ES1_3 ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 scalar_t__ twl6040_get_revid (struct twl6040*) ; 

int twl6040_get_hs_step_size(struct snd_soc_component *component)
{
	struct twl6040 *twl6040 = to_twl6040(component);

	if (twl6040_get_revid(twl6040) < TWL6040_REV_ES1_3)
		/* For ES under ES_1.3 HS step is 2 mV */
		return 2;
	else
		/* For ES_1.3 HS step is 1 mV */
		return 1;
}