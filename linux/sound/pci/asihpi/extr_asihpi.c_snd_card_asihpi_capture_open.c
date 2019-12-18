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
struct snd_pcm_substream {int /*<<< orphan*/  number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_hardware {size_t buffer_bytes_max; size_t period_bytes_min; size_t period_bytes_max; size_t periods_min; size_t periods_max; int info; int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  channels_max; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; int /*<<< orphan*/  private_free; struct snd_card_asihpi_pcm* private_data; } ;
struct snd_card_asihpi_pcm {int /*<<< orphan*/  h_stream; struct snd_pcm_substream* substream; int /*<<< orphan*/  timer; } ;
struct snd_card_asihpi {size_t update_interval_frames; size_t out_max_chans; scalar_t__ can_dma; scalar_t__ support_grouping; int /*<<< orphan*/  in_min_chans; int /*<<< orphan*/  in_max_chans; TYPE_2__* hpi; } ;
typedef  int /*<<< orphan*/  snd_card_asihpi_capture ;
struct TYPE_4__ {int /*<<< orphan*/  interrupt_mode; TYPE_1__* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 size_t BUFFER_BYTES_MAX ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HPI_ERROR_OBJ_ALREADY_OPEN ; 
 size_t PERIODS_MIN ; 
 size_t PERIOD_BYTES_MIN ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int SNDRV_PCM_INFO_INTERLEAVED ; 
 int SNDRV_PCM_INFO_MMAP ; 
 int SNDRV_PCM_INFO_MMAP_VALID ; 
 int SNDRV_PCM_INFO_SYNC_START ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_instream_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_card_asihpi_pcm*) ; 
 struct snd_card_asihpi_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_pcm_hardware*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_card_asihpi_capture_formats (struct snd_card_asihpi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_asihpi_pcm_samplerates (struct snd_card_asihpi*,struct snd_pcm_hardware*) ; 
 int /*<<< orphan*/  snd_card_asihpi_runtime_free ; 
 int /*<<< orphan*/  snd_card_asihpi_timer_function ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_pow2 (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct snd_card_asihpi* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_card_asihpi_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	struct snd_card_asihpi_pcm *dpcm;
	struct snd_pcm_hardware snd_card_asihpi_capture;
	int err;

	dpcm = kzalloc(sizeof(*dpcm), GFP_KERNEL);
	if (dpcm == NULL)
		return -ENOMEM;

	snd_printdd("capture open adapter %d stream %d\n",
			card->hpi->adapter->index, substream->number);

	err = hpi_handle_error(
	    hpi_instream_open(card->hpi->adapter->index,
			     substream->number, &dpcm->h_stream));
	if (err)
		kfree(dpcm);
	if (err == HPI_ERROR_OBJ_ALREADY_OPEN)
		return -EBUSY;
	if (err)
		return -EIO;

	timer_setup(&dpcm->timer, snd_card_asihpi_timer_function, 0);
	dpcm->substream = substream;
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_asihpi_runtime_free;

	memset(&snd_card_asihpi_capture, 0, sizeof(snd_card_asihpi_capture));
	if (!card->hpi->interrupt_mode) {
		snd_card_asihpi_capture.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_capture.period_bytes_min = PERIOD_BYTES_MIN;
		snd_card_asihpi_capture.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_capture.periods_min = PERIODS_MIN;
		snd_card_asihpi_capture.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN;
	} else {
		size_t pbmin = card->update_interval_frames *
			card->out_max_chans;
		snd_card_asihpi_capture.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_capture.period_bytes_min = pbmin;
		snd_card_asihpi_capture.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_capture.periods_min = PERIODS_MIN;
		snd_card_asihpi_capture.periods_max = BUFFER_BYTES_MAX / pbmin;
	}
	/* snd_card_asihpi_capture.fifo_size = 0; */
	snd_card_asihpi_capture.channels_max = card->in_max_chans;
	snd_card_asihpi_capture.channels_min = card->in_min_chans;
	snd_card_asihpi_capture.formats =
		snd_card_asihpi_capture_formats(card, dpcm->h_stream);
	snd_card_asihpi_pcm_samplerates(card,  &snd_card_asihpi_capture);
	snd_card_asihpi_capture.info = SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_MMAP_VALID;

	if (card->support_grouping)
		snd_card_asihpi_capture.info |= SNDRV_PCM_INFO_SYNC_START;

	runtime->hw = snd_card_asihpi_capture;

	if (card->can_dma)
		err = snd_pcm_hw_constraint_pow2(runtime, 0,
					SNDRV_PCM_HW_PARAM_BUFFER_BYTES);
	if (err < 0)
		return err;

	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_interval_frames);
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_interval_frames, UINT_MAX);

	snd_pcm_set_sync(substream);

	return 0;
}