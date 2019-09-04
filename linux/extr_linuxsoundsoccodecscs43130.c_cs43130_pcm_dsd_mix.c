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
 int /*<<< orphan*/  CS43130_DSD_PCM_MIX_CTL ; 
 int /*<<< orphan*/  CS43130_MIX_PCM_DSD_MASK ; 
 int CS43130_MIX_PCM_DSD_SHIFT ; 
 int /*<<< orphan*/  CS43130_MIX_PCM_PREP_MASK ; 
 int CS43130_MIX_PCM_PREP_SHIFT ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs43130_pcm_dsd_mix(bool en, struct regmap *regmap)
{
	if (en) {
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_PREP_MASK,
				   1 << CS43130_MIX_PCM_PREP_SHIFT);
		usleep_range(6000, 6050);
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_DSD_MASK,
				   1 << CS43130_MIX_PCM_DSD_SHIFT);
	} else {
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_DSD_MASK,
				   0 << CS43130_MIX_PCM_DSD_SHIFT);
		usleep_range(1600, 1650);
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_PREP_MASK,
				   0 << CS43130_MIX_PCM_PREP_SHIFT);
	}

	return 0;
}