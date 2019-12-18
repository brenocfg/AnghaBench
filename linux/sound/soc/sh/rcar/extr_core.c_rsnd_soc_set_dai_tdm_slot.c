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
struct snd_soc_dai {int dummy; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rsnd_priv* rsnd_dai_to_priv (struct snd_soc_dai*) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_rdai_channels_set (struct rsnd_dai*,int) ; 
 int /*<<< orphan*/  rsnd_rdai_ssi_lane_set (struct rsnd_dai*,int) ; 
 int /*<<< orphan*/  rsnd_rdai_width_set (struct rsnd_dai*,int) ; 

__attribute__((used)) static int rsnd_soc_set_dai_tdm_slot(struct snd_soc_dai *dai,
				     u32 tx_mask, u32 rx_mask,
				     int slots, int slot_width)
{
	struct rsnd_priv *priv = rsnd_dai_to_priv(dai);
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct device *dev = rsnd_priv_to_dev(priv);

	switch (slot_width) {
	case 16:
	case 24:
	case 32:
		break;
	default:
		/* use default */
		slot_width = 32;
	}

	switch (slots) {
	case 2:
		/* TDM Split Mode */
	case 6:
	case 8:
		/* TDM Extend Mode */
		rsnd_rdai_channels_set(rdai, slots);
		rsnd_rdai_ssi_lane_set(rdai, 1);
		rsnd_rdai_width_set(rdai, slot_width);
		break;
	default:
		dev_err(dev, "unsupported TDM slots (%d)\n", slots);
		return -EINVAL;
	}

	return 0;
}