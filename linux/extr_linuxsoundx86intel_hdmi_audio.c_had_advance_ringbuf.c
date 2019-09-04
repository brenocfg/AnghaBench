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
struct snd_intelhad {int pcmbuf_head; } ;
struct TYPE_2__ {int periods; } ;

/* Variables and functions */
 int /*<<< orphan*/  had_prog_bd (struct snd_pcm_substream*,struct snd_intelhad*) ; 

__attribute__((used)) static void had_advance_ringbuf(struct snd_pcm_substream *substream,
				struct snd_intelhad *intelhaddata)
{
	int num_periods = substream->runtime->periods;

	/* reprogram the next buffer */
	had_prog_bd(substream, intelhaddata);

	/* proceed to next */
	intelhaddata->pcmbuf_head++;
	intelhaddata->pcmbuf_head %= num_periods;
}