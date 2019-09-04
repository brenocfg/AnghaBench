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
 int /*<<< orphan*/  MAX9850_CHARGE_PUMP ; 
 int /*<<< orphan*/  MAX9850_GENERAL_PURPOSE ; 
 int /*<<< orphan*/  MAX9850_VOLUME ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max9850_probe(struct snd_soc_component *component)
{
	/* enable zero-detect */
	snd_soc_component_update_bits(component, MAX9850_GENERAL_PURPOSE, 1, 1);
	/* enable slew-rate control */
	snd_soc_component_update_bits(component, MAX9850_VOLUME, 0x40, 0x40);
	/* set slew-rate 125ms */
	snd_soc_component_update_bits(component, MAX9850_CHARGE_PUMP, 0xff, 0xc0);

	return 0;
}