#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct loopback_pcm* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {void** bits; } ;
struct loopback_pcm {TYPE_2__* loopback; struct loopback_cable* cable; } ;
struct TYPE_3__ {int formats; } ;
struct loopback_cable {TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  cable_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int snd_mask_refine (int /*<<< orphan*/ ,struct snd_mask*) ; 

__attribute__((used)) static int rule_format(struct snd_pcm_hw_params *params,
		       struct snd_pcm_hw_rule *rule)
{
	struct loopback_pcm *dpcm = rule->private;
	struct loopback_cable *cable = dpcm->cable;
	struct snd_mask m;

	snd_mask_none(&m);
	mutex_lock(&dpcm->loopback->cable_lock);
	m.bits[0] = (u_int32_t)cable->hw.formats;
	m.bits[1] = (u_int32_t)(cable->hw.formats >> 32);
	mutex_unlock(&dpcm->loopback->cable_lock);
	return snd_mask_refine(hw_param_mask(params, rule->var), &m);
}