#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_emu8k_pcm {int dummy; } ;
struct TYPE_2__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILL_SILENCE ; 
 int /*<<< orphan*/  LOOP_WRITE (struct snd_emu8k_pcm*,unsigned long,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long bytes_to_frames (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static int emu8k_pcm_silence(struct snd_pcm_substream *subs,
			     int voice, unsigned long pos, unsigned long count)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;

	/* convert to frames */
	pos = bytes_to_frames(subs->runtime, pos);
	count = bytes_to_frames(subs->runtime, count);
	LOOP_WRITE(rec, pos, NULL, count, FILL_SILENCE);
	return 0;
}