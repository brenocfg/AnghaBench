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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_DACMUTE ; 
 int /*<<< orphan*/  AIC32X4_MUTEON ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic32x4_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;

	snd_soc_component_update_bits(component, AIC32X4_DACMUTE,
				AIC32X4_MUTEON, mute ? AIC32X4_MUTEON : 0);

	return 0;
}