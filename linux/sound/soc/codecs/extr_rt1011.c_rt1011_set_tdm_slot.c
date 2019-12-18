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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RT1011_ADCDAT1_OUTPUT ; 
 int RT1011_ADCDAT1_PIN_CONFIG ; 
 unsigned int RT1011_ADCDAT2_OUTPUT ; 
 int RT1011_ADCDAT2_PIN_CONFIG ; 
 unsigned int RT1011_I2S_CH_RX_LEN_20B ; 
 unsigned int RT1011_I2S_CH_RX_LEN_24B ; 
 unsigned int RT1011_I2S_CH_RX_LEN_32B ; 
 int RT1011_I2S_CH_RX_LEN_MASK ; 
 int RT1011_I2S_CH_RX_MASK ; 
 unsigned int RT1011_I2S_CH_TX_LEN_20B ; 
 unsigned int RT1011_I2S_CH_TX_LEN_24B ; 
 unsigned int RT1011_I2S_CH_TX_LEN_32B ; 
 int RT1011_I2S_CH_TX_LEN_MASK ; 
 int RT1011_I2S_CH_TX_MASK ; 
 unsigned int RT1011_I2S_RX_4CH ; 
 unsigned int RT1011_I2S_RX_6CH ; 
 unsigned int RT1011_I2S_RX_8CH ; 
 unsigned int RT1011_I2S_TX_4CH ; 
 unsigned int RT1011_I2S_TX_6CH ; 
 unsigned int RT1011_I2S_TX_8CH ; 
 int /*<<< orphan*/  RT1011_TDM1_SET_1 ; 
 int /*<<< orphan*/  RT1011_TDM1_SET_2 ; 
 int /*<<< orphan*/  RT1011_TDM2_SET_1 ; 
 int /*<<< orphan*/  RT1011_TDM2_SET_2 ; 
 unsigned int RT1011_TDM_I2S_DOCK_EN_1 ; 
 int RT1011_TDM_I2S_DOCK_EN_1_MASK ; 
 int RT1011_TDM_I2S_DOCK_EN_2_MASK ; 
 int /*<<< orphan*/  RT1011_TDM_TOTAL_SET ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int rt1011_set_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	unsigned int val = 0, tdm_en = 0;
	int ret = 0;

	snd_soc_dapm_mutex_lock(dapm);
	if (rx_mask || tx_mask)
		tdm_en = RT1011_TDM_I2S_DOCK_EN_1;

	switch (slots) {
	case 4:
		val |= RT1011_I2S_TX_4CH;
		val |= RT1011_I2S_RX_4CH;
		break;
	case 6:
		val |= RT1011_I2S_TX_6CH;
		val |= RT1011_I2S_RX_6CH;
		break;
	case 8:
		val |= RT1011_I2S_TX_8CH;
		val |= RT1011_I2S_RX_8CH;
		break;
	case 2:
		break;
	default:
		ret = -EINVAL;
	}

	switch (slot_width) {
	case 20:
		val |= RT1011_I2S_CH_TX_LEN_20B;
		val |= RT1011_I2S_CH_RX_LEN_20B;
		break;
	case 24:
		val |= RT1011_I2S_CH_TX_LEN_24B;
		val |= RT1011_I2S_CH_RX_LEN_24B;
		break;
	case 32:
		val |= RT1011_I2S_CH_TX_LEN_32B;
		val |= RT1011_I2S_CH_RX_LEN_32B;
		break;
	case 16:
		break;
	default:
		ret = -EINVAL;
	}

	snd_soc_component_update_bits(component, RT1011_TDM1_SET_1,
		RT1011_I2S_CH_TX_MASK | RT1011_I2S_CH_RX_MASK |
		RT1011_I2S_CH_TX_LEN_MASK |	RT1011_I2S_CH_RX_LEN_MASK, val);
	snd_soc_component_update_bits(component, RT1011_TDM2_SET_1,
		RT1011_I2S_CH_TX_MASK | RT1011_I2S_CH_RX_MASK |
		RT1011_I2S_CH_TX_LEN_MASK |	RT1011_I2S_CH_RX_LEN_MASK, val);
	snd_soc_component_update_bits(component, RT1011_TDM1_SET_2,
		RT1011_TDM_I2S_DOCK_EN_1_MASK,	tdm_en);
	snd_soc_component_update_bits(component, RT1011_TDM2_SET_2,
		RT1011_TDM_I2S_DOCK_EN_2_MASK,	tdm_en);
	snd_soc_component_update_bits(component, RT1011_TDM_TOTAL_SET,
		RT1011_ADCDAT1_PIN_CONFIG | RT1011_ADCDAT2_PIN_CONFIG,
		RT1011_ADCDAT1_OUTPUT | RT1011_ADCDAT2_OUTPUT);

	snd_soc_dapm_mutex_unlock(dapm);
	return ret;
}