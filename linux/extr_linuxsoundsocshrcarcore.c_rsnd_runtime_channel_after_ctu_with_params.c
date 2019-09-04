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
typedef  int u32 ;
struct snd_pcm_hw_params {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int rsnd_ctu_converted_channel (struct rsnd_mod*) ; 
 struct rsnd_mod* rsnd_io_to_mod_ctu (struct rsnd_dai_stream*) ; 
 int rsnd_runtime_channel_original_with_params (struct rsnd_dai_stream*,struct snd_pcm_hw_params*) ; 

int rsnd_runtime_channel_after_ctu_with_params(struct rsnd_dai_stream *io,
					       struct snd_pcm_hw_params *params)
{
	int chan = rsnd_runtime_channel_original_with_params(io, params);
	struct rsnd_mod *ctu_mod = rsnd_io_to_mod_ctu(io);

	if (ctu_mod) {
		u32 converted_chan = rsnd_ctu_converted_channel(ctu_mod);

		if (converted_chan)
			return converted_chan;
	}

	return chan;
}