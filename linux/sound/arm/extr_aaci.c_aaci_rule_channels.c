#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct aaci* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aaci {TYPE_2__* ac97_bus; } ;
struct TYPE_6__ {unsigned int slots; } ;
struct TYPE_5__ {TYPE_1__* pcms; } ;
struct TYPE_4__ {TYPE_3__* r; } ;

/* Variables and functions */
 int AC97_SLOT_LFE ; 
 int AC97_SLOT_PCM_SLEFT ; 
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 

__attribute__((used)) static int aaci_rule_channels(struct snd_pcm_hw_params *p,
	struct snd_pcm_hw_rule *rule)
{
	static unsigned int channel_list[] = { 2, 4, 6 };
	struct aaci *aaci = rule->private;
	unsigned int mask = 1 << 0, slots;

	/* pcms[0] is the our 5.1 PCM instance. */
	slots = aaci->ac97_bus->pcms[0].r[0].slots;
	if (slots & (1 << AC97_SLOT_PCM_SLEFT)) {
		mask |= 1 << 1;
		if (slots & (1 << AC97_SLOT_LFE))
			mask |= 1 << 2;
	}

	return snd_interval_list(hw_param_interval(p, rule->var),
				 ARRAY_SIZE(channel_list), channel_list, mask);
}