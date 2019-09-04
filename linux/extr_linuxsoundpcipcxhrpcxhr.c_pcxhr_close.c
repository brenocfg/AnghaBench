#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {int /*<<< orphan*/  chip_idx; TYPE_2__* card; struct pcxhr_mgr* mgr; } ;
struct snd_pcm_substream {int /*<<< orphan*/  number; TYPE_1__* runtime; } ;
struct pcxhr_stream {int /*<<< orphan*/ * substream; int /*<<< orphan*/  status; } ;
struct pcxhr_mgr {scalar_t__ ref_count_rate; int /*<<< orphan*/  setup_mutex; scalar_t__ sample_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct pcxhr_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_STREAM_STATUS_FREE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_hardware_timer (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 struct snd_pcxhr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcxhr_close(struct snd_pcm_substream *subs)
{
	struct snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	struct pcxhr_mgr *mgr = chip->mgr;
	struct pcxhr_stream *stream = subs->runtime->private_data;

	mutex_lock(&mgr->setup_mutex);

	dev_dbg(chip->card->dev, "pcxhr_close chip%d subs%d\n",
		    chip->chip_idx, subs->number);

	/* sample rate released */
	if (--mgr->ref_count_rate == 0) {
		mgr->sample_rate = 0;	/* the sample rate is no more locked */
		pcxhr_hardware_timer(mgr, 0);	/* stop the DSP-timer */
	}

	stream->status    = PCXHR_STREAM_STATUS_FREE;
	stream->substream = NULL;

	mutex_unlock(&mgr->setup_mutex);

	return 0;
}