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
struct TYPE_2__ {int /*<<< orphan*/  sw_buffer_size; int /*<<< orphan*/  hw_buffer_size; } ;
struct hal2_codec {struct snd_pcm_substream* substream; TYPE_1__ pcm_indirect; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  voices; } ;
struct snd_hal2 {struct hal2_codec dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2_BUF_SIZE ; 
 int /*<<< orphan*/  hal2_compute_rate (struct hal2_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal2_setup_dac (struct snd_hal2*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct hal2_codec *dac = &hal2->dac;

	dac->voices = runtime->channels;
	dac->sample_rate = hal2_compute_rate(dac, runtime->rate);
	memset(&dac->pcm_indirect, 0, sizeof(dac->pcm_indirect));
	dac->pcm_indirect.hw_buffer_size = H2_BUF_SIZE;
	dac->pcm_indirect.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	dac->substream = substream;
	hal2_setup_dac(hal2);
	return 0;
}