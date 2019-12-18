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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; int /*<<< orphan*/  channels; } ;
struct TYPE_2__ {int hw_buffer_size; int hw_queue_size; int /*<<< orphan*/  sw_buffer_size; int /*<<< orphan*/  hw_io; } ;
struct hal2_codec {struct snd_pcm_substream* substream; TYPE_1__ pcm_indirect; int /*<<< orphan*/  buffer_dma; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  voices; } ;
struct snd_hal2 {struct hal2_codec adc; } ;

/* Variables and functions */
 int H2_BUF_SIZE ; 
 int /*<<< orphan*/  hal2_compute_rate (struct hal2_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal2_setup_adc (struct snd_hal2*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hal2_codec *adc = &hal2->adc;

	adc->voices = runtime->channels;
	adc->sample_rate = hal2_compute_rate(adc, runtime->rate);
	memset(&adc->pcm_indirect, 0, sizeof(adc->pcm_indirect));
	adc->pcm_indirect.hw_buffer_size = H2_BUF_SIZE;
	adc->pcm_indirect.hw_queue_size = H2_BUF_SIZE / 2;
	adc->pcm_indirect.hw_io = adc->buffer_dma;
	adc->pcm_indirect.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	adc->substream = substream;
	hal2_setup_adc(hal2);
	return 0;
}