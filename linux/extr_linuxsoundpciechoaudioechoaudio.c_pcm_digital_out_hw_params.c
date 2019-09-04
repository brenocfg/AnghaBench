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
struct snd_pcm_substream {scalar_t__ number; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct echoaudio {int dummy; } ;

/* Variables and functions */
 int init_engine (struct snd_pcm_substream*,struct snd_pcm_hw_params*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ px_digital_out (struct echoaudio*) ; 
 struct echoaudio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_digital_out_hw_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *hw_params)
{
	struct echoaudio *chip = snd_pcm_substream_chip(substream);

	return init_engine(substream, hw_params, px_digital_out(chip) +
			substream->number, params_channels(hw_params));
}