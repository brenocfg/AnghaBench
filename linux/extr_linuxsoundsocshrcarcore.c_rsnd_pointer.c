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
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_dai_call (int /*<<< orphan*/ ,struct rsnd_dai_stream*,int /*<<< orphan*/ *) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 struct rsnd_dai_stream* rsnd_rdai_to_io (struct rsnd_dai*,struct snd_pcm_substream*) ; 
 struct snd_soc_dai* rsnd_substream_to_dai (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t rsnd_pointer(struct snd_pcm_substream *substream)
{
	struct snd_soc_dai *dai = rsnd_substream_to_dai(substream);
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	snd_pcm_uframes_t pointer = 0;

	rsnd_dai_call(pointer, io, &pointer);

	return pointer;
}