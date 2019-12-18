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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct snd_pcm_indirect2 {int /*<<< orphan*/  sw_io; int /*<<< orphan*/  pointer_calls; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

snd_pcm_uframes_t
snd_pcm_indirect2_pointer(struct snd_pcm_substream *substream,
			  struct snd_pcm_indirect2 *rec)
{
#ifdef SND_PCM_INDIRECT2_STAT
	rec->pointer_calls++;
#endif
	return bytes_to_frames(substream->runtime, rec->sw_io);
}