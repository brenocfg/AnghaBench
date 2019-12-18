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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  rsnd_dai_call (int /*<<< orphan*/ ,struct rsnd_dai_stream*,struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_dai_stream_quit (struct rsnd_dai_stream*) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 struct rsnd_dai_stream* rsnd_rdai_to_io (struct rsnd_dai*,struct snd_pcm_substream*) ; 
 struct rsnd_priv* rsnd_rdai_to_priv (struct rsnd_dai*) ; 

__attribute__((used)) static void rsnd_soc_dai_shutdown(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	struct rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);

	/*
	 * call rsnd_dai_call without spinlock
	 */
	rsnd_dai_call(cleanup, io, priv);

	rsnd_dai_stream_quit(io);
}