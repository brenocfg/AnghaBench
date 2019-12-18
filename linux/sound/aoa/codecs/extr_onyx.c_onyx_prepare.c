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
typedef  int u8 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct onyx {int analog_locked; int spdif_locked; int /*<<< orphan*/  mutex; } ;
struct codec_info_item {struct onyx* codec_data; } ;
struct bus_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ format; int rate; } ;

/* Variables and functions */
 int EBUSY ; 
 int ONYX_MUTE_LEFT ; 
 int ONYX_MUTE_RIGHT ; 
 int /*<<< orphan*/  ONYX_REG_DAC_CONTROL ; 
 int /*<<< orphan*/  ONYX_REG_DIG_INFO4 ; 
 int ONYX_SPDIF_ENABLE ; 
 scalar_t__ SNDRV_PCM_FMTBIT_COMPRESSED_16BE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ onyx_write_register (struct onyx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int onyx_prepare(struct codec_info_item *cii,
			struct bus_info *bi,
			struct snd_pcm_substream *substream)
{
	u8 v;
	struct onyx *onyx = cii->codec_data;
	int err = -EBUSY;

	mutex_lock(&onyx->mutex);

#ifdef SNDRV_PCM_FMTBIT_COMPRESSED_16BE
	if (substream->runtime->format == SNDRV_PCM_FMTBIT_COMPRESSED_16BE) {
		/* mute and lock analog output */
		onyx_read_register(onyx, ONYX_REG_DAC_CONTROL, &v);
		if (onyx_write_register(onyx,
					ONYX_REG_DAC_CONTROL,
					v | ONYX_MUTE_RIGHT | ONYX_MUTE_LEFT))
			goto out_unlock;
		onyx->analog_locked = 1;
		err = 0;
		goto out_unlock;
	}
#endif
	switch (substream->runtime->rate) {
	case 32000:
	case 44100:
	case 48000:
		/* these rates are ok for all outputs */
		/* FIXME: program spdif channel control bits here so that
		 *	  userspace doesn't have to if it only plays pcm! */
		err = 0;
		goto out_unlock;
	default:
		/* got some rate that the digital output can't do,
		 * so disable and lock it */
		onyx_read_register(cii->codec_data, ONYX_REG_DIG_INFO4, &v);
		if (onyx_write_register(onyx,
					ONYX_REG_DIG_INFO4,
					v & ~ONYX_SPDIF_ENABLE))
			goto out_unlock;
		onyx->spdif_locked = 1;
		err = 0;
		goto out_unlock;
	}

 out_unlock:
	mutex_unlock(&onyx->mutex);

	return err;
}