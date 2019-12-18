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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct azx_pcm {struct azx* chip; } ;
struct TYPE_2__ {scalar_t__ format_val; scalar_t__ period_bytes; scalar_t__ bufsize; } ;
struct azx_dev {TYPE_1__ core; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ dsp_is_locked (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_lock (struct azx_dev*) ; 
 int /*<<< orphan*/  dsp_unlock (struct azx_dev*) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  trace_azx_pcm_hw_params (struct azx*,struct azx_dev*) ; 

__attribute__((used)) static int azx_pcm_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *hw_params)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx *chip = apcm->chip;
	struct azx_dev *azx_dev = get_azx_dev(substream);
	int ret;

	trace_azx_pcm_hw_params(chip, azx_dev);
	dsp_lock(azx_dev);
	if (dsp_is_locked(azx_dev)) {
		ret = -EBUSY;
		goto unlock;
	}

	azx_dev->core.bufsize = 0;
	azx_dev->core.period_bytes = 0;
	azx_dev->core.format_val = 0;
	ret = snd_pcm_lib_malloc_pages(substream,
				       params_buffer_bytes(hw_params));

unlock:
	dsp_unlock(azx_dev);
	return ret;
}