#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {size_t number; struct snd_pcm* pcm; struct snd_pcm_runtime* runtime; } ;
struct TYPE_5__ {scalar_t__ rate_max; scalar_t__ rate_min; } ;
struct snd_pcm_runtime {TYPE_2__ hw; struct mixart_stream* private_data; } ;
struct snd_pcm {int dummy; } ;
struct snd_mixart {struct mixart_mgr* mgr; TYPE_1__* card; int /*<<< orphan*/  chip_idx; struct mixart_stream** playback_stream; struct snd_pcm* pcm_dig; struct snd_pcm* pcm; } ;
struct mixart_stream {scalar_t__ status; int pcm_number; scalar_t__ channels; struct snd_pcm_substream* substream; struct mixart_pipe* pipe; } ;
struct mixart_pipe {int dummy; } ;
struct mixart_mgr {int /*<<< orphan*/  setup_mutex; scalar_t__ sample_rate; int /*<<< orphan*/  ref_count_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MIXART_PCM_ANALOG ; 
 int MIXART_PCM_DIGITAL ; 
 scalar_t__ MIXART_STREAM_STATUS_FREE ; 
 scalar_t__ MIXART_STREAM_STATUS_OPEN ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int mixart_set_pipe_state (struct mixart_mgr*,struct mixart_pipe*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 struct mixart_pipe* snd_mixart_add_ref_pipe (struct snd_mixart*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ snd_mixart_analog_caps ; 
 TYPE_2__ snd_mixart_digital_caps ; 
 int /*<<< orphan*/  snd_mixart_kill_ref_pipe (struct mixart_mgr*,struct mixart_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_mixart* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_mixart_playback_open(struct snd_pcm_substream *subs)
{
	struct snd_mixart            *chip = snd_pcm_substream_chip(subs);
	struct mixart_mgr        *mgr = chip->mgr;
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct snd_pcm *pcm = subs->pcm;
	struct mixart_stream     *stream;
	struct mixart_pipe       *pipe;
	int err = 0;
	int pcm_number;

	mutex_lock(&mgr->setup_mutex);

	if ( pcm == chip->pcm ) {
		pcm_number = MIXART_PCM_ANALOG;
		runtime->hw = snd_mixart_analog_caps;
	} else {
		snd_BUG_ON(pcm != chip->pcm_dig);
		pcm_number = MIXART_PCM_DIGITAL;
		runtime->hw = snd_mixart_digital_caps;
	}
	dev_dbg(chip->card->dev,
		"snd_mixart_playback_open C%d/P%d/Sub%d\n",
		chip->chip_idx, pcm_number, subs->number);

	/* get stream info */
	stream = &(chip->playback_stream[pcm_number][subs->number]);

	if (stream->status != MIXART_STREAM_STATUS_FREE){
		/* streams in use */
		dev_err(chip->card->dev,
			"snd_mixart_playback_open C%d/P%d/Sub%d in use\n",
			chip->chip_idx, pcm_number, subs->number);
		err = -EBUSY;
		goto _exit_open;
	}

	/* get pipe pointer (out pipe) */
	pipe = snd_mixart_add_ref_pipe(chip, pcm_number, 0, 0);

	if (pipe == NULL) {
		err = -EINVAL;
		goto _exit_open;
	}

	/* start the pipe if necessary */
	err = mixart_set_pipe_state(chip->mgr, pipe, 1);
	if( err < 0 ) {
		dev_err(chip->card->dev, "error starting pipe!\n");
		snd_mixart_kill_ref_pipe(chip->mgr, pipe, 0);
		err = -EINVAL;
		goto _exit_open;
	}

	stream->pipe        = pipe;
	stream->pcm_number  = pcm_number;
	stream->status      = MIXART_STREAM_STATUS_OPEN;
	stream->substream   = subs;
	stream->channels    = 0; /* not configured yet */

	runtime->private_data = stream;

	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 64);

	/* if a sample rate is already used, another stream cannot change */
	if(mgr->ref_count_rate++) {
		if(mgr->sample_rate) {
			runtime->hw.rate_min = runtime->hw.rate_max = mgr->sample_rate;
		}
	}

 _exit_open:
	mutex_unlock(&mgr->setup_mutex);

	return err;
}