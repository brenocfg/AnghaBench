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
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct loopback_pcm* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {scalar_t__ integer; scalar_t__ openmax; scalar_t__ openmin; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct loopback_pcm {TYPE_2__* loopback; struct loopback_cable* cable; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct loopback_cable {TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  cable_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_interval_refine (int /*<<< orphan*/ ,struct snd_interval*) ; 

__attribute__((used)) static int rule_rate(struct snd_pcm_hw_params *params,
		     struct snd_pcm_hw_rule *rule)
{
	struct loopback_pcm *dpcm = rule->private;
	struct loopback_cable *cable = dpcm->cable;
	struct snd_interval t;

	mutex_lock(&dpcm->loopback->cable_lock);
	t.min = cable->hw.rate_min;
	t.max = cable->hw.rate_max;
	mutex_unlock(&dpcm->loopback->cable_lock);
        t.openmin = t.openmax = 0;
        t.integer = 0;
	return snd_interval_refine(hw_param_interval(params, rule->var), &t);
}