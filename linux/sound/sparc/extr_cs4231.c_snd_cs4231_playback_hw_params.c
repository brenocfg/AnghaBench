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
struct snd_cs4231 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 unsigned char snd_cs4231_get_format (struct snd_cs4231*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char snd_cs4231_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4231_playback_format (struct snd_cs4231*,struct snd_pcm_hw_params*,unsigned char) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_cs4231* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs4231_playback_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *hw_params)
{
	struct snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	unsigned char new_pdfr;
	int err;

	err = snd_pcm_lib_malloc_pages(substream,
					params_buffer_bytes(hw_params));
	if (err < 0)
		return err;
	new_pdfr = snd_cs4231_get_format(chip, params_format(hw_params),
					 params_channels(hw_params)) |
		snd_cs4231_get_rate(params_rate(hw_params));
	snd_cs4231_playback_format(chip, hw_params, new_pdfr);

	return 0;
}