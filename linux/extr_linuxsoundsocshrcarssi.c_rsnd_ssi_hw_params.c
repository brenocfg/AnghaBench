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
struct rsnd_ssi {int chan; scalar_t__ usrcnt; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_ssi_hw_params(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	int chan = params_channels(params);

	/*
	 * snd_pcm_ops::hw_params will be called *before*
	 * snd_soc_dai_ops::trigger. Thus, ssi->usrcnt is 0
	 * in 1st call.
	 */
	if (ssi->usrcnt) {
		/*
		 * Already working.
		 * It will happen if SSI has parent/child connection.
		 * it is error if child <-> parent SSI uses
		 * different channels.
		 */
		if (ssi->chan != chan)
			return -EIO;
	}

	ssi->chan = chan;

	return 0;
}