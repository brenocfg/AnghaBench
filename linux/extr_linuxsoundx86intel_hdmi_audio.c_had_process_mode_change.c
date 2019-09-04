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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_intelhad {int /*<<< orphan*/  link_rate; scalar_t__ dp_output; int /*<<< orphan*/  dev; int /*<<< orphan*/  tmds_clock_speed; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  had_enable_audio (struct snd_intelhad*,int) ; 
 int /*<<< orphan*/  had_prog_cts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_intelhad*) ; 
 int had_prog_n (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_intelhad*) ; 
 struct snd_pcm_substream* had_substream_get (struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_substream_put (struct snd_intelhad*) ; 

__attribute__((used)) static int had_process_mode_change(struct snd_intelhad *intelhaddata)
{
	struct snd_pcm_substream *substream;
	int retval = 0;
	u32 disp_samp_freq, n_param;
	u32 link_rate = 0;

	substream = had_substream_get(intelhaddata);
	if (!substream)
		return 0;

	/* Disable Audio */
	had_enable_audio(intelhaddata, false);

	/* Update CTS value */
	disp_samp_freq = intelhaddata->tmds_clock_speed;

	retval = had_prog_n(substream->runtime->rate, &n_param, intelhaddata);
	if (retval) {
		dev_err(intelhaddata->dev,
			"programming N value failed %#x\n", retval);
		goto out;
	}

	if (intelhaddata->dp_output)
		link_rate = intelhaddata->link_rate;

	had_prog_cts(substream->runtime->rate, disp_samp_freq, link_rate,
		     n_param, intelhaddata);

	/* Enable Audio */
	had_enable_audio(intelhaddata, true);

out:
	had_substream_put(intelhaddata);
	return retval;
}