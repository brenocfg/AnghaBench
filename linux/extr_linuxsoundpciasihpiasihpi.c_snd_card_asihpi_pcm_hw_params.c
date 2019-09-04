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
typedef  int /*<<< orphan*/  u16 ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_addr; struct snd_card_asihpi_pcm* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_card_asihpi_pcm {unsigned int bytes_per_sec; int /*<<< orphan*/  period_bytes; int /*<<< orphan*/  buffer_bytes; scalar_t__ hpi_buffer_attached; int /*<<< orphan*/  h_stream; int /*<<< orphan*/  format; } ;
struct snd_card_asihpi {scalar_t__ can_dma; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  hpi_format_create (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 scalar_t__ hpi_instream_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ hpi_instream_set_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hpi_stream_get_info_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hpi_stream_host_buffer_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  print_hwparams (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int snd_card_asihpi_format_alsa2hpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_card_asihpi* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printd (char*,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int snd_card_asihpi_pcm_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_card_asihpi_pcm *dpcm = runtime->private_data;
	struct snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	int err;
	u16 format;
	int width;
	unsigned int bytes_per_sec;

	print_hwparams(substream, params);
	err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(params));
	if (err < 0)
		return err;
	err = snd_card_asihpi_format_alsa2hpi(params_format(params), &format);
	if (err)
		return err;

	hpi_handle_error(hpi_format_create(&dpcm->format,
			params_channels(params),
			format, params_rate(params), 0, 0));

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		if (hpi_instream_reset(dpcm->h_stream) != 0)
			return -EINVAL;

		if (hpi_instream_set_format(
			dpcm->h_stream, &dpcm->format) != 0)
			return -EINVAL;
	}

	dpcm->hpi_buffer_attached = 0;
	if (card->can_dma) {
		err = hpi_stream_host_buffer_attach(dpcm->h_stream,
			params_buffer_bytes(params),  runtime->dma_addr);
		if (err == 0) {
			snd_printdd(
				"stream_host_buffer_attach success %u %lu\n",
				params_buffer_bytes(params),
				(unsigned long)runtime->dma_addr);
		} else {
			snd_printd("stream_host_buffer_attach error %d\n",
					err);
			return -ENOMEM;
		}

		err = hpi_stream_get_info_ex(dpcm->h_stream, NULL,
				&dpcm->hpi_buffer_attached, NULL, NULL, NULL);
	}
	bytes_per_sec = params_rate(params) * params_channels(params);
	width = snd_pcm_format_width(params_format(params));
	bytes_per_sec *= width;
	bytes_per_sec /= 8;
	if (width < 0 || bytes_per_sec == 0)
		return -EINVAL;

	dpcm->bytes_per_sec = bytes_per_sec;
	dpcm->buffer_bytes = params_buffer_bytes(params);
	dpcm->period_bytes = params_period_bytes(params);

	return 0;
}