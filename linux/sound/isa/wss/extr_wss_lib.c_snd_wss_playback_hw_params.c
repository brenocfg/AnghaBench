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
struct snd_wss {int /*<<< orphan*/  (* set_playback_format ) (struct snd_wss*,struct snd_pcm_hw_params*,unsigned char) ;} ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_wss* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 unsigned char snd_wss_get_format (struct snd_wss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char snd_wss_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_wss*,struct snd_pcm_hw_params*,unsigned char) ; 

__attribute__((used)) static int snd_wss_playback_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *hw_params)
{
	struct snd_wss *chip = snd_pcm_substream_chip(substream);
	unsigned char new_pdfr;
	int err;

	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;
	new_pdfr = snd_wss_get_format(chip, params_format(hw_params),
				params_channels(hw_params)) |
				snd_wss_get_rate(params_rate(hw_params));
	chip->set_playback_format(chip, hw_params, new_pdfr);
	return 0;
}