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
struct snd_pcm_oss_setup {scalar_t__ block; scalar_t__ nonblock; } ;
struct TYPE_3__ {int oss; struct snd_pcm_oss_setup setup; } ;
struct snd_pcm_substream {int /*<<< orphan*/  pcm_release; struct snd_pcm_runtime* runtime; int /*<<< orphan*/  f_flags; TYPE_1__ oss; } ;
struct TYPE_4__ {int params; int trigger; int rate; int channels; int /*<<< orphan*/  rw_ref; scalar_t__ subdivision; scalar_t__ maxfrags; scalar_t__ fragshift; int /*<<< orphan*/  format; int /*<<< orphan*/  params_lock; } ;
struct snd_pcm_runtime {TYPE_2__ oss; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_MU_LAW ; 
 int /*<<< orphan*/  AFMT_S16_LE ; 
 int /*<<< orphan*/  AFMT_U8 ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int SNDRV_MINOR_OSS_DEVICE (int) ; 
#define  SNDRV_MINOR_OSS_PCM_16 129 
#define  SNDRV_MINOR_OSS_PCM_8 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_oss_release_substream ; 

__attribute__((used)) static void snd_pcm_oss_init_substream(struct snd_pcm_substream *substream,
				       struct snd_pcm_oss_setup *setup,
				       int minor)
{
	struct snd_pcm_runtime *runtime;

	substream->oss.oss = 1;
	substream->oss.setup = *setup;
	if (setup->nonblock)
		substream->f_flags |= O_NONBLOCK;
	else if (setup->block)
		substream->f_flags &= ~O_NONBLOCK;
	runtime = substream->runtime;
	runtime->oss.params = 1;
	runtime->oss.trigger = 1;
	runtime->oss.rate = 8000;
	mutex_init(&runtime->oss.params_lock);
	switch (SNDRV_MINOR_OSS_DEVICE(minor)) {
	case SNDRV_MINOR_OSS_PCM_8:
		runtime->oss.format = AFMT_U8;
		break;
	case SNDRV_MINOR_OSS_PCM_16:
		runtime->oss.format = AFMT_S16_LE;
		break;
	default:
		runtime->oss.format = AFMT_MU_LAW;
	}
	runtime->oss.channels = 1;
	runtime->oss.fragshift = 0;
	runtime->oss.maxfrags = 0;
	runtime->oss.subdivision = 0;
	substream->pcm_release = snd_pcm_oss_release_substream;
	atomic_set(&runtime->oss.rw_ref, 0);
}