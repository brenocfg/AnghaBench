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
typedef  int u32 ;
struct TYPE_2__ {int mute; } ;
struct spdif_out_dev {scalar_t__ io_base; scalar_t__ running; TYPE_1__ saved_params; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int SPDIF_OPMODE_AUD_DATA ; 
 int SPDIF_OPMODE_MASK ; 
 int SPDIF_OPMODE_MUTE_PCM ; 
 int SPDIF_OPMODE_OFF ; 
 scalar_t__ SPDIF_OUT_CTRL ; 
 int SPDIF_STATE_NORMAL ; 
 int readl (scalar_t__) ; 
 struct spdif_out_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spdif_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct spdif_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 val;

	host->saved_params.mute = mute;
	val = readl(host->io_base + SPDIF_OUT_CTRL);
	val &= ~SPDIF_OPMODE_MASK;

	if (mute)
		val |= SPDIF_OPMODE_MUTE_PCM;
	else {
		if (host->running)
			val |= SPDIF_OPMODE_AUD_DATA | SPDIF_STATE_NORMAL;
		else
			val |= SPDIF_OPMODE_OFF;
	}

	writel(val, host->io_base + SPDIF_OUT_CTRL);
	return 0;
}