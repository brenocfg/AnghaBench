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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rsnd_io_converted_chan (struct rsnd_dai_stream*) ; 
 struct rsnd_mod* rsnd_io_to_mod_ctu (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_io_to_priv (struct rsnd_dai_stream*) ; 
 struct device* rsnd_priv_to_dev (int /*<<< orphan*/ ) ; 
 int rsnd_runtime_channel_original_with_params (struct rsnd_dai_stream*,struct snd_pcm_hw_params*) ; 
 scalar_t__ rsnd_runtime_is_tdm_split (struct rsnd_dai_stream*) ; 

int rsnd_runtime_channel_after_ctu_with_params(struct rsnd_dai_stream *io,
					       struct snd_pcm_hw_params *params)
{
	int chan = rsnd_runtime_channel_original_with_params(io, params);
	struct rsnd_mod *ctu_mod = rsnd_io_to_mod_ctu(io);

	if (ctu_mod) {
		u32 converted_chan = rsnd_io_converted_chan(io);

		/*
		 * !! Note !!
		 *
		 * converted_chan will be used for CTU,
		 * or TDM Split mode.
		 * User shouldn't use CTU with TDM Split mode.
		 */
		if (rsnd_runtime_is_tdm_split(io)) {
			struct device *dev = rsnd_priv_to_dev(rsnd_io_to_priv(io));

			dev_err(dev, "CTU and TDM Split should be used\n");
		}

		if (converted_chan)
			return converted_chan;
	}

	return chan;
}