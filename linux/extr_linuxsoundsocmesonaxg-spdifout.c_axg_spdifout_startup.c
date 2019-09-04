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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct axg_spdifout {int /*<<< orphan*/  map; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIFOUT_CTRL0 ; 
 int SPDIFOUT_CTRL0_CHSTS_SEL ; 
 int SPDIFOUT_CTRL0_DATA_SEL ; 
 int SPDIFOUT_CTRL0_MSB_FIRST ; 
 int SPDIFOUT_CTRL0_USEL ; 
 int SPDIFOUT_CTRL0_USET ; 
 int SPDIFOUT_CTRL0_VSEL ; 
 int /*<<< orphan*/  SPDIFOUT_SWAP ; 
 int /*<<< orphan*/  axg_spdifout_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct axg_spdifout* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_spdifout_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct axg_spdifout *priv = snd_soc_dai_get_drvdata(dai);
	int ret;

	/* Clock the spdif output block */
	ret = clk_prepare_enable(priv->pclk);
	if (ret) {
		dev_err(dai->dev, "failed to enable pclk\n");
		return ret;
	}

	/* Make sure the block is initially stopped */
	axg_spdifout_disable(priv->map);

	/* Insert data from bit 27 lsb first */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MSB_FIRST | SPDIFOUT_CTRL0_DATA_SEL,
			   0);

	/* Manual control of V, C and U, U = 0 */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_CHSTS_SEL | SPDIFOUT_CTRL0_VSEL |
			   SPDIFOUT_CTRL0_USEL | SPDIFOUT_CTRL0_USET,
			   0);

	/* Static SWAP configuration ATM */
	regmap_write(priv->map, SPDIFOUT_SWAP, 0x10);

	return 0;
}