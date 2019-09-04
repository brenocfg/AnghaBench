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
struct snd_pcm_runtime {int periods; int /*<<< orphan*/  period_size; } ;
struct snd_intelhad {int num_bds; int period_bytes; scalar_t__ bd_head; scalar_t__ pcmbuf_filled; scalar_t__ pcmbuf_head; } ;

/* Variables and functions */
 int HAD_NUM_OF_RING_BUFS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  had_invalidate_bd (struct snd_intelhad*,int) ; 
 int /*<<< orphan*/  had_prog_bd (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int max (int,unsigned int) ; 
 int min (int,int) ; 

__attribute__((used)) static void had_init_ringbuf(struct snd_pcm_substream *substream,
			     struct snd_intelhad *intelhaddata)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int i, num_periods;

	num_periods = runtime->periods;
	intelhaddata->num_bds = min(num_periods, HAD_NUM_OF_RING_BUFS);
	/* set the minimum 2 BDs for num_periods=1 */
	intelhaddata->num_bds = max(intelhaddata->num_bds, 2U);
	intelhaddata->period_bytes =
		frames_to_bytes(runtime, runtime->period_size);
	WARN_ON(intelhaddata->period_bytes & 0x3f);

	intelhaddata->bd_head = 0;
	intelhaddata->pcmbuf_head = 0;
	intelhaddata->pcmbuf_filled = 0;

	for (i = 0; i < HAD_NUM_OF_RING_BUFS; i++) {
		if (i < intelhaddata->num_bds)
			had_prog_bd(substream, intelhaddata);
		else /* invalidate the rest */
			had_invalidate_bd(intelhaddata, i);
	}

	intelhaddata->bd_head = 0; /* reset at head again before starting */
}