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
typedef  int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSD_MR ; 
 int CLASSD_MR_LMUTE_MASK ; 
 int CLASSD_MR_RMUTE_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int atmel_classd_codec_dai_digital_mute(struct snd_soc_dai *codec_dai,
	int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	u32 mask, val;

	mask = CLASSD_MR_LMUTE_MASK | CLASSD_MR_RMUTE_MASK;

	if (mute)
		val = mask;
	else
		val = 0;

	snd_soc_component_update_bits(component, CLASSD_MR, mask, val);

	return 0;
}