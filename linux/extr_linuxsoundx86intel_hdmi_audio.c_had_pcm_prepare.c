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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int periods; int rate; int channels; int /*<<< orphan*/  period_size; } ;
struct snd_intelhad {int /*<<< orphan*/  link_rate; scalar_t__ dp_output; int /*<<< orphan*/  dev; int /*<<< orphan*/  tmds_clock_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BUF_CH_SWAP ; 
 int /*<<< orphan*/  SWAP_LFE_CENTER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  had_do_reset (struct snd_intelhad*) ; 
 int had_init_audio_ctrl (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_init_ringbuf (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_prog_cts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_prog_dip (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int had_prog_n (int,int /*<<< orphan*/ *,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int had_pcm_prepare(struct snd_pcm_substream *substream)
{
	int retval;
	u32 disp_samp_freq, n_param;
	u32 link_rate = 0;
	struct snd_intelhad *intelhaddata;
	struct snd_pcm_runtime *runtime;

	intelhaddata = snd_pcm_substream_chip(substream);
	runtime = substream->runtime;

	dev_dbg(intelhaddata->dev, "period_size=%d\n",
		(int)frames_to_bytes(runtime, runtime->period_size));
	dev_dbg(intelhaddata->dev, "periods=%d\n", runtime->periods);
	dev_dbg(intelhaddata->dev, "buffer_size=%d\n",
		(int)snd_pcm_lib_buffer_bytes(substream));
	dev_dbg(intelhaddata->dev, "rate=%d\n", runtime->rate);
	dev_dbg(intelhaddata->dev, "channels=%d\n", runtime->channels);

	had_do_reset(intelhaddata);

	/* Get N value in KHz */
	disp_samp_freq = intelhaddata->tmds_clock_speed;

	retval = had_prog_n(substream->runtime->rate, &n_param, intelhaddata);
	if (retval) {
		dev_err(intelhaddata->dev,
			"programming N value failed %#x\n", retval);
		goto prep_end;
	}

	if (intelhaddata->dp_output)
		link_rate = intelhaddata->link_rate;

	had_prog_cts(substream->runtime->rate, disp_samp_freq, link_rate,
		     n_param, intelhaddata);

	had_prog_dip(substream, intelhaddata);

	retval = had_init_audio_ctrl(substream, intelhaddata);

	/* Prog buffer address */
	had_init_ringbuf(substream, intelhaddata);

	/*
	 * Program channel mapping in following order:
	 * FL, FR, C, LFE, RL, RR
	 */

	had_write_register(intelhaddata, AUD_BUF_CH_SWAP, SWAP_LFE_CENTER);

prep_end:
	return retval;
}