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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct skl_pipe_params {int /*<<< orphan*/  stream; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int skl_tplg_be_update_params (struct snd_soc_dai*,struct skl_pipe_params*) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_be_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct skl_pipe_params p_params = {0};

	p_params.s_fmt = snd_pcm_format_width(params_format(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.stream = substream->stream;

	return skl_tplg_be_update_params(dai, &p_params);
}