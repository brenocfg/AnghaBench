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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct acp_platform_info {int /*<<< orphan*/  capture_channel; int /*<<< orphan*/  i2s_instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHANNEL0 ; 
 int /*<<< orphan*/  I2S_SP_INSTANCE ; 
 int da7219_clk_enable (struct snd_pcm_substream*) ; 
 struct acp_platform_info* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int cz_dmic1_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct acp_platform_info *machine = snd_soc_card_get_drvdata(card);

	machine->i2s_instance = I2S_SP_INSTANCE;
	machine->capture_channel = CAP_CHANNEL0;
	return da7219_clk_enable(substream);
}