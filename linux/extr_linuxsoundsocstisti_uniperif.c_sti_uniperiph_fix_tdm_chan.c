#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  avail_slots; } ;
struct uniperif {TYPE_1__ tdm_slot; } ;
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct uniperif* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {scalar_t__ integer; scalar_t__ openmax; scalar_t__ openmin; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

int sti_uniperiph_fix_tdm_chan(struct snd_pcm_hw_params *params,
			       struct snd_pcm_hw_rule *rule)
{
	struct uniperif *uni = rule->private;
	struct snd_interval t;

	t.min = uni->tdm_slot.avail_slots;
	t.max = uni->tdm_slot.avail_slots;
	t.openmin = 0;
	t.openmax = 0;
	t.integer = 0;

	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}