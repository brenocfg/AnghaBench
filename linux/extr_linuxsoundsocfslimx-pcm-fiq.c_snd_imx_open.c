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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct imx_pcm_runtime_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct imx_pcm_runtime_data {TYPE_1__ hrt; int /*<<< orphan*/  capturing; int /*<<< orphan*/  playing; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct imx_pcm_runtime_data*) ; 
 struct imx_pcm_runtime_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hrtimer_callback ; 
 int /*<<< orphan*/  snd_imx_hardware ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_imx_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct imx_pcm_runtime_data *iprtd;
	int ret;

	iprtd = kzalloc(sizeof(*iprtd), GFP_KERNEL);
	if (iprtd == NULL)
		return -ENOMEM;
	runtime->private_data = iprtd;

	iprtd->substream = substream;

	atomic_set(&iprtd->playing, 0);
	atomic_set(&iprtd->capturing, 0);
	hrtimer_init(&iprtd->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	iprtd->hrt.function = snd_hrtimer_callback;

	ret = snd_pcm_hw_constraint_integer(substream->runtime,
			SNDRV_PCM_HW_PARAM_PERIODS);
	if (ret < 0) {
		kfree(iprtd);
		return ret;
	}

	snd_soc_set_runtime_hwparams(substream, &snd_imx_hardware);
	return 0;
}