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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int (* pcm_transfer_f ) (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interleaved_copy(struct snd_pcm_substream *substream,
			    snd_pcm_uframes_t hwoff, void *data,
			    snd_pcm_uframes_t off,
			    snd_pcm_uframes_t frames,
			    pcm_transfer_f transfer)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	/* convert to bytes */
	hwoff = frames_to_bytes(runtime, hwoff);
	off = frames_to_bytes(runtime, off);
	frames = frames_to_bytes(runtime, frames);
	return transfer(substream, 0, hwoff, data + off, frames);
}