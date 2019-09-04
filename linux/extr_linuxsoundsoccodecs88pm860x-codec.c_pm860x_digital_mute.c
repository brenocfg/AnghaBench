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
 int MUTE_LEFT ; 
 int MUTE_RIGHT ; 
 int /*<<< orphan*/  PM860X_DAC_OFFSET ; 
 int /*<<< orphan*/  PM860X_EAR_CTRL_2 ; 
 int RSYNC_CHANGE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pm860x_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	int data = 0, mask = MUTE_LEFT | MUTE_RIGHT;

	if (mute)
		data = mask;
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, mask, data);
	snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
			    RSYNC_CHANGE, RSYNC_CHANGE);
	return 0;
}