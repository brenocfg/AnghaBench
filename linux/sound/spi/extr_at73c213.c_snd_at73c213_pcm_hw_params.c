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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_at73c213 {TYPE_1__* ssc; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int SSC_BFINS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TFMR ; 
 int /*<<< orphan*/  TFMR_DATNB ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_at73c213* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_at73c213_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *hw_params)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	int channels = params_channels(hw_params);
	int val;

	val = ssc_readl(chip->ssc->regs, TFMR);
	val = SSC_BFINS(TFMR_DATNB, channels - 1, val);
	ssc_writel(chip->ssc->regs, TFMR, val);

	return snd_pcm_lib_malloc_pages(substream,
					params_buffer_bytes(hw_params));
}