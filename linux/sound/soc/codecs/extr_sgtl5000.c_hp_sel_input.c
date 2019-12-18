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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_CTRL ; 
 int SGTL5000_HP_SEL_MASK ; 
 int SGTL5000_HP_SEL_SHIFT ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hp_sel_input(struct snd_soc_component *component)
{
	return (snd_soc_component_read32(component, SGTL5000_CHIP_ANA_CTRL) &
		SGTL5000_HP_SEL_MASK) >> SGTL5000_HP_SEL_SHIFT;
}