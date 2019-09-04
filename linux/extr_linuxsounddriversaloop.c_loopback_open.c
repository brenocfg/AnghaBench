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
struct snd_pcm_substream {size_t number; size_t stream; struct loopback* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {void* hw; int /*<<< orphan*/  private_free; struct loopback_pcm* private_data; } ;
struct loopback_pcm {struct loopback_cable* cable; int /*<<< orphan*/  timer; struct snd_pcm_substream* substream; struct loopback* loopback; } ;
struct loopback_cable {int /*<<< orphan*/  lock; struct loopback_pcm** streams; void* hw; } ;
struct loopback {int /*<<< orphan*/  cable_lock; struct loopback_cable*** cables; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  free_cable (struct snd_pcm_substream*) ; 
 int get_cable_index (struct snd_pcm_substream*) ; 
 scalar_t__ get_notify (struct loopback_pcm*) ; 
 int /*<<< orphan*/  kfree (struct loopback_pcm*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* loopback_pcm_hardware ; 
 int /*<<< orphan*/  loopback_runtime_free ; 
 int /*<<< orphan*/  loopback_timer_function ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rule_channels ; 
 int /*<<< orphan*/  rule_format ; 
 int /*<<< orphan*/  rule_rate ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct loopback_pcm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loopback_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback *loopback = substream->private_data;
	struct loopback_pcm *dpcm;
	struct loopback_cable *cable = NULL;
	int err = 0;
	int dev = get_cable_index(substream);

	mutex_lock(&loopback->cable_lock);
	dpcm = kzalloc(sizeof(*dpcm), GFP_KERNEL);
	if (!dpcm) {
		err = -ENOMEM;
		goto unlock;
	}
	dpcm->loopback = loopback;
	dpcm->substream = substream;
	timer_setup(&dpcm->timer, loopback_timer_function, 0);

	cable = loopback->cables[substream->number][dev];
	if (!cable) {
		cable = kzalloc(sizeof(*cable), GFP_KERNEL);
		if (!cable) {
			err = -ENOMEM;
			goto unlock;
		}
		spin_lock_init(&cable->lock);
		cable->hw = loopback_pcm_hardware;
		loopback->cables[substream->number][dev] = cable;
	}
	dpcm->cable = cable;

	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);

	/* use dynamic rules based on actual runtime->hw values */
	/* note that the default rules created in the PCM midlevel code */
	/* are cached -> they do not reflect the actual state */
	err = snd_pcm_hw_rule_add(runtime, 0,
				  SNDRV_PCM_HW_PARAM_FORMAT,
				  rule_format, dpcm,
				  SNDRV_PCM_HW_PARAM_FORMAT, -1);
	if (err < 0)
		goto unlock;
	err = snd_pcm_hw_rule_add(runtime, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  rule_rate, dpcm,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		goto unlock;
	err = snd_pcm_hw_rule_add(runtime, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  rule_channels, dpcm,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (err < 0)
		goto unlock;

	runtime->private_data = dpcm;
	runtime->private_free = loopback_runtime_free;
	if (get_notify(dpcm))
		runtime->hw = loopback_pcm_hardware;
	else
		runtime->hw = cable->hw;

	spin_lock_irq(&cable->lock);
	cable->streams[substream->stream] = dpcm;
	spin_unlock_irq(&cable->lock);

 unlock:
	if (err < 0) {
		free_cable(substream);
		kfree(dpcm);
	}
	mutex_unlock(&loopback->cable_lock);
	return err;
}