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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES8316_DAC_SET1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int es8316_mute(struct snd_soc_dai *dai, int mute)
{
	snd_soc_component_update_bits(dai->component, ES8316_DAC_SET1, 0x20,
			    mute ? 0x20 : 0);
	return 0;
}