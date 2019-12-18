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
struct sun4i_spdif_dev {int /*<<< orphan*/  regmap; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_SPDIF_CTL ; 
 int /*<<< orphan*/  SUN4I_SPDIF_CTL_GEN ; 
 int /*<<< orphan*/  SUN4I_SPDIF_INT ; 
 int /*<<< orphan*/  SUN4I_SPDIF_INT_TXDRQEN ; 
 int /*<<< orphan*/  SUN4I_SPDIF_TXCFG ; 
 int /*<<< orphan*/  SUN4I_SPDIF_TXCFG_SINGLEMOD ; 
 int /*<<< orphan*/  SUN4I_SPDIF_TXCFG_TXEN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_snd_txctrl_on(struct snd_pcm_substream *substream,
				struct sun4i_spdif_dev *host)
{
	if (substream->runtime->channels == 1)
		regmap_update_bits(host->regmap, SUN4I_SPDIF_TXCFG,
				   SUN4I_SPDIF_TXCFG_SINGLEMOD,
				   SUN4I_SPDIF_TXCFG_SINGLEMOD);

	/* SPDIF TX ENABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_TXCFG,
			   SUN4I_SPDIF_TXCFG_TXEN, SUN4I_SPDIF_TXCFG_TXEN);

	/* DRQ ENABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_INT,
			   SUN4I_SPDIF_INT_TXDRQEN, SUN4I_SPDIF_INT_TXDRQEN);

	/* Global enable */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_CTL,
			   SUN4I_SPDIF_CTL_GEN, SUN4I_SPDIF_CTL_GEN);
}