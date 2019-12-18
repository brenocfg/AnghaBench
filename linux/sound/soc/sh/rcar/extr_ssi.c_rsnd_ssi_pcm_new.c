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
struct snd_soc_pcm_runtime {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_ssi_parent_attach (struct rsnd_mod*,struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_pcm_new(struct rsnd_mod *mod,
			    struct rsnd_dai_stream *io,
			    struct snd_soc_pcm_runtime *rtd)
{
	/*
	 * rsnd_rdai_is_clk_master() will be enabled after set_fmt,
	 * and, pcm_new will be called after it.
	 * This function reuse pcm_new at this point.
	 */
	rsnd_ssi_parent_attach(mod, io);

	return 0;
}