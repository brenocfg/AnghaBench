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
struct snd_pcm_substream {int /*<<< orphan*/  number; TYPE_1__* runtime; } ;
struct snd_mixart {int /*<<< orphan*/  chip_idx; TYPE_2__* card; struct mixart_mgr* mgr; } ;
struct mixart_stream {int /*<<< orphan*/ * substream; int /*<<< orphan*/  status; int /*<<< orphan*/ * pipe; int /*<<< orphan*/  pcm_number; } ;
struct mixart_mgr {scalar_t__ ref_count_rate; int /*<<< orphan*/  setup_mutex; scalar_t__ sample_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct mixart_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_STREAM_STATUS_FREE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_mixart_kill_ref_pipe (struct mixart_mgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_mixart* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_mixart_close(struct snd_pcm_substream *subs)
{
	struct snd_mixart *chip = snd_pcm_substream_chip(subs);
	struct mixart_mgr *mgr = chip->mgr;
	struct mixart_stream *stream = subs->runtime->private_data;

	mutex_lock(&mgr->setup_mutex);

	dev_dbg(chip->card->dev, "snd_mixart_close C%d/P%d/Sub%d\n",
		chip->chip_idx, stream->pcm_number, subs->number);

	/* sample rate released */
	if(--mgr->ref_count_rate == 0) {
		mgr->sample_rate = 0;
	}

	/* delete pipe */
	if (snd_mixart_kill_ref_pipe(mgr, stream->pipe, 0 ) < 0) {

		dev_err(chip->card->dev,
			"error snd_mixart_kill_ref_pipe C%dP%d\n",
			chip->chip_idx, stream->pcm_number);
	}

	stream->pipe      = NULL;
	stream->status    = MIXART_STREAM_STATUS_FREE;
	stream->substream = NULL;

	mutex_unlock(&mgr->setup_mutex);
	return 0;
}