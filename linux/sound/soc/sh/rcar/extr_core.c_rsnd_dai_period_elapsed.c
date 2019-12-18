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
struct rsnd_dai_stream {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

void rsnd_dai_period_elapsed(struct rsnd_dai_stream *io)
{
	struct snd_pcm_substream *substream = io->substream;

	/*
	 * this function should be called...
	 *
	 * - if rsnd_dai_pointer_update() returns true
	 * - without spin lock
	 */

	snd_pcm_period_elapsed(substream);
}