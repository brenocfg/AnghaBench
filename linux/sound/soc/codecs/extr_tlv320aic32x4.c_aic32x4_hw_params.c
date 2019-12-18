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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aic32x4_priv {scalar_t__ swapdacs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_DACSETUP ; 
 int /*<<< orphan*/  AIC32X4_DAC_CHAN_MASK ; 
 int /*<<< orphan*/  AIC32X4_IFACE1 ; 
 int /*<<< orphan*/  AIC32X4_IFACE1_DATALEN_MASK ; 
 int AIC32X4_IFACE1_DATALEN_SHIFT ; 
 int AIC32X4_LDAC2LCHN ; 
 int AIC32X4_LDAC2RCHN ; 
 int AIC32X4_RDAC2LCHN ; 
 int AIC32X4_RDAC2RCHN ; 
 int AIC32X4_WORD_LEN_16BITS ; 
 int AIC32X4_WORD_LEN_20BITS ; 
 int AIC32X4_WORD_LEN_24BITS ; 
 int AIC32X4_WORD_LEN_32BITS ; 
 int /*<<< orphan*/  aic32x4_setup_clocks (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct aic32x4_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic32x4_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct aic32x4_priv *aic32x4 = snd_soc_component_get_drvdata(component);
	u8 iface1_reg = 0;
	u8 dacsetup_reg = 0;

	aic32x4_setup_clocks(component, params_rate(params));

	switch (params_width(params)) {
	case 16:
		iface1_reg |= (AIC32X4_WORD_LEN_16BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		break;
	case 20:
		iface1_reg |= (AIC32X4_WORD_LEN_20BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		break;
	case 24:
		iface1_reg |= (AIC32X4_WORD_LEN_24BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		break;
	case 32:
		iface1_reg |= (AIC32X4_WORD_LEN_32BITS <<
				   AIC32X4_IFACE1_DATALEN_SHIFT);
		break;
	}
	snd_soc_component_update_bits(component, AIC32X4_IFACE1,
				AIC32X4_IFACE1_DATALEN_MASK, iface1_reg);

	if (params_channels(params) == 1) {
		dacsetup_reg = AIC32X4_RDAC2LCHN | AIC32X4_LDAC2LCHN;
	} else {
		if (aic32x4->swapdacs)
			dacsetup_reg = AIC32X4_RDAC2LCHN | AIC32X4_LDAC2RCHN;
		else
			dacsetup_reg = AIC32X4_LDAC2LCHN | AIC32X4_RDAC2RCHN;
	}
	snd_soc_component_update_bits(component, AIC32X4_DACSETUP,
				AIC32X4_DAC_CHAN_MASK, dacsetup_reg);

	return 0;
}