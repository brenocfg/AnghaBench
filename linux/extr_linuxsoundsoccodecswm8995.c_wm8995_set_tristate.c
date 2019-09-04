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
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8995_AIF1_MASTER_SLAVE ; 
 int WM8995_AIF1_TRI ; 
 int WM8995_AIF2_MASTER_SLAVE ; 
 int WM8995_AIF2_TRI ; 
 int WM8995_AIF3_TRI ; 
 int WM8995_POWER_MANAGEMENT_5 ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm8995_set_tristate(struct snd_soc_dai *codec_dai, int tristate)
{
	struct snd_soc_component *component = codec_dai->component;
	int reg, val, mask;

	switch (codec_dai->id) {
	case 0:
		reg = WM8995_AIF1_MASTER_SLAVE;
		mask = WM8995_AIF1_TRI;
		break;
	case 1:
		reg = WM8995_AIF2_MASTER_SLAVE;
		mask = WM8995_AIF2_TRI;
		break;
	case 2:
		reg = WM8995_POWER_MANAGEMENT_5;
		mask = WM8995_AIF3_TRI;
		break;
	default:
		return -EINVAL;
	}

	if (tristate)
		val = mask;
	else
		val = 0;

	return snd_soc_component_update_bits(component, reg, mask, val);
}