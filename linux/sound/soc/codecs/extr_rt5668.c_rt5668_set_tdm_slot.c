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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RT5668_TDM_CL_16 ; 
 unsigned int RT5668_TDM_CL_20 ; 
 unsigned int RT5668_TDM_CL_24 ; 
 unsigned int RT5668_TDM_CL_32 ; 
 int RT5668_TDM_CL_MASK ; 
 int /*<<< orphan*/  RT5668_TDM_CTRL ; 
 unsigned int RT5668_TDM_RX_CH_4 ; 
 unsigned int RT5668_TDM_RX_CH_6 ; 
 unsigned int RT5668_TDM_RX_CH_8 ; 
 int RT5668_TDM_RX_CH_MASK ; 
 int /*<<< orphan*/  RT5668_TDM_TCON_CTRL ; 
 unsigned int RT5668_TDM_TX_CH_4 ; 
 unsigned int RT5668_TDM_TX_CH_6 ; 
 unsigned int RT5668_TDM_TX_CH_8 ; 
 int RT5668_TDM_TX_CH_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rt5668_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0;

	switch (slots) {
	case 4:
		val |= RT5668_TDM_TX_CH_4;
		val |= RT5668_TDM_RX_CH_4;
		break;
	case 6:
		val |= RT5668_TDM_TX_CH_6;
		val |= RT5668_TDM_RX_CH_6;
		break;
	case 8:
		val |= RT5668_TDM_TX_CH_8;
		val |= RT5668_TDM_RX_CH_8;
		break;
	case 2:
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT5668_TDM_CTRL,
		RT5668_TDM_TX_CH_MASK | RT5668_TDM_RX_CH_MASK, val);

	switch (slot_width) {
	case 16:
		val = RT5668_TDM_CL_16;
		break;
	case 20:
		val = RT5668_TDM_CL_20;
		break;
	case 24:
		val = RT5668_TDM_CL_24;
		break;
	case 32:
		val = RT5668_TDM_CL_32;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT5668_TDM_TCON_CTRL,
		RT5668_TDM_CL_MASK, val);

	return 0;
}