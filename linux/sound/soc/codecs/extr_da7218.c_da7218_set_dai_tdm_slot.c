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
typedef  unsigned int u8 ;
typedef  int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7218_2BYTE_MASK ; 
 unsigned int DA7218_2BYTE_SHIFT ; 
 unsigned int DA7218_BYTE_MASK ; 
 unsigned int DA7218_BYTE_SHIFT ; 
 unsigned int DA7218_DAI_BCLKS_PER_WCLK_128 ; 
 unsigned int DA7218_DAI_BCLKS_PER_WCLK_256 ; 
 unsigned int DA7218_DAI_BCLKS_PER_WCLK_32 ; 
 unsigned int DA7218_DAI_BCLKS_PER_WCLK_64 ; 
 unsigned int DA7218_DAI_BCLKS_PER_WCLK_MASK ; 
 int /*<<< orphan*/  DA7218_DAI_CLK_MODE ; 
 int /*<<< orphan*/  DA7218_DAI_OFFSET_LOWER ; 
 int /*<<< orphan*/  DA7218_DAI_OFFSET_UPPER ; 
 unsigned int DA7218_DAI_TDM_CH_EN_MASK ; 
 unsigned int DA7218_DAI_TDM_CH_EN_SHIFT ; 
 int /*<<< orphan*/  DA7218_DAI_TDM_CTRL ; 
 scalar_t__ DA7218_DAI_TDM_MAX_SLOTS ; 
 unsigned int DA7218_DAI_TDM_MODE_EN_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fls (unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da7218_set_dai_tdm_slot(struct snd_soc_dai *dai,
				   unsigned int tx_mask, unsigned int rx_mask,
				   int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	u8 dai_bclks_per_wclk;
	u32 frame_size;

	/* No channels enabled so disable TDM, revert to 64-bit frames */
	if (!tx_mask) {
		snd_soc_component_update_bits(component, DA7218_DAI_TDM_CTRL,
				    DA7218_DAI_TDM_CH_EN_MASK |
				    DA7218_DAI_TDM_MODE_EN_MASK, 0);
		snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
				    DA7218_DAI_BCLKS_PER_WCLK_MASK,
				    DA7218_DAI_BCLKS_PER_WCLK_64);
		return 0;
	}

	/* Check we have valid slots */
	if (fls(tx_mask) > DA7218_DAI_TDM_MAX_SLOTS) {
		dev_err(component->dev, "Invalid number of slots, max = %d\n",
			DA7218_DAI_TDM_MAX_SLOTS);
		return -EINVAL;
	}

	/* Check we have a valid offset given (first 2 bytes of rx_mask) */
	if (rx_mask >> DA7218_2BYTE_SHIFT) {
		dev_err(component->dev, "Invalid slot offset, max = %d\n",
			DA7218_2BYTE_MASK);
		return -EINVAL;
	}

	/* Calculate & validate frame size based on slot info provided. */
	frame_size = slots * slot_width;
	switch (frame_size) {
	case 32:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_32;
		break;
	case 64:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_64;
		break;
	case 128:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_128;
		break;
	case 256:
		dai_bclks_per_wclk = DA7218_DAI_BCLKS_PER_WCLK_256;
		break;
	default:
		dev_err(component->dev, "Invalid frame size\n");
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, DA7218_DAI_CLK_MODE,
			    DA7218_DAI_BCLKS_PER_WCLK_MASK,
			    dai_bclks_per_wclk);
	snd_soc_component_write(component, DA7218_DAI_OFFSET_LOWER,
		      (rx_mask & DA7218_BYTE_MASK));
	snd_soc_component_write(component, DA7218_DAI_OFFSET_UPPER,
		      ((rx_mask >> DA7218_BYTE_SHIFT) & DA7218_BYTE_MASK));
	snd_soc_component_update_bits(component, DA7218_DAI_TDM_CTRL,
			    DA7218_DAI_TDM_CH_EN_MASK |
			    DA7218_DAI_TDM_MODE_EN_MASK,
			    (tx_mask << DA7218_DAI_TDM_CH_EN_SHIFT) |
			    DA7218_DAI_TDM_MODE_EN_MASK);

	return 0;
}