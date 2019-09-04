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
typedef  scalar_t__ u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_VC_REG09 ; 
 scalar_t__ DAVINCI_VC_REG09_MUTE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cq93vc_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	u8 reg;

	if (mute)
		reg = DAVINCI_VC_REG09_MUTE;
	else
		reg = 0;

	snd_soc_component_update_bits(component, DAVINCI_VC_REG09, DAVINCI_VC_REG09_MUTE,
			    reg);

	return 0;
}