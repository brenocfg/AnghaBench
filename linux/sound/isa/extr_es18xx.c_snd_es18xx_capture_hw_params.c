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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_es18xx {int caps; int dma1_shift; scalar_t__ playback_a_substream; } ;

/* Variables and functions */
 int EBUSY ; 
 int ES18XX_DUPLEX_MONO ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  _snd_pcm_hw_param_setempty (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es18xx_capture_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct snd_es18xx *chip = snd_pcm_substream_chip(substream);
	int shift, err;

	shift = 0;
	if ((chip->caps & ES18XX_DUPLEX_MONO) &&
	    chip->playback_a_substream &&
	    params_channels(hw_params) != 1) {
		_snd_pcm_hw_param_setempty(hw_params, SNDRV_PCM_HW_PARAM_CHANNELS);
		return -EBUSY;
	}
	if (params_channels(hw_params) == 2)
		shift++;
	if (snd_pcm_format_width(params_format(hw_params)) == 16)
		shift++;
	chip->dma1_shift = shift;
	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;
	return 0;
}