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
struct snd_pcm_runtime {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 struct snd_pcm_runtime* rsnd_io_to_runtime (struct rsnd_dai_stream*) ; 

int rsnd_kctrl_accept_runtime(struct rsnd_dai_stream *io)
{
	struct snd_pcm_runtime *runtime = rsnd_io_to_runtime(io);

	return !!runtime;
}