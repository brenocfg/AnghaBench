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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int da7219_clk_enable (struct snd_pcm_substream*,int,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cz_da7219_params(struct snd_pcm_substream *substream,
				      struct snd_pcm_hw_params *params)
{
	int wclk, bclk;

	wclk = params_rate(params);
	bclk = wclk * params_channels(params) *
		snd_pcm_format_width(params_format(params));
	/* ADAU7002 spec: "The ADAU7002 requires a BCLK rate
	 * that is minimum of 64x the LRCLK sample rate."
	 * DA7219 is the only clk source so for all codecs
	 * we have to limit bclk to 64X lrclk.
	 */
	if (bclk < (wclk * 64))
		bclk = wclk * 64;
	return da7219_clk_enable(substream, wclk, bclk);
}