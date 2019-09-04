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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dapm_widget {scalar_t__ reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MICB_1_CTL ; 
 int /*<<< orphan*/  CDC_A_TX_1_2_TEST_CTL_2 ; 
#define  CDC_A_TX_1_EN 133 
#define  CDC_A_TX_2_EN 132 
#define  CDC_A_TX_3_EN 131 
 int /*<<< orphan*/  CDC_D_CDC_CONN_TX1_CTL ; 
 int /*<<< orphan*/  CDC_D_CDC_CONN_TX2_CTL ; 
 int CONN_TX1_SERIAL_TX1_ADC_1 ; 
 int CONN_TX1_SERIAL_TX1_MUX ; 
 int CONN_TX1_SERIAL_TX1_ZERO ; 
 int CONN_TX2_SERIAL_TX2_ADC_2 ; 
 int CONN_TX2_SERIAL_TX2_MUX ; 
 int CONN_TX2_SERIAL_TX2_ZERO ; 
 int MICB_1_CTL_CFILT_REF_SEL_HPF_REF ; 
 int MICB_1_CTL_CFILT_REF_SEL_MASK ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pm8916_wcd_analog_enable_adc(struct snd_soc_dapm_widget *w,
					 struct snd_kcontrol *kcontrol,
					 int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 adc_reg = CDC_A_TX_1_2_TEST_CTL_2;
	u8 init_bit_shift;

	if (w->reg == CDC_A_TX_1_EN)
		init_bit_shift = 5;
	else
		init_bit_shift = 4;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (w->reg == CDC_A_TX_2_EN)
			snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
					    MICB_1_CTL_CFILT_REF_SEL_MASK,
					    MICB_1_CTL_CFILT_REF_SEL_HPF_REF);
		/*
		 * Add delay of 10 ms to give sufficient time for the voltage
		 * to shoot up and settle so that the txfe init does not
		 * happen when the input voltage is changing too much.
		 */
		usleep_range(10000, 10010);
		snd_soc_component_update_bits(component, adc_reg, 1 << init_bit_shift,
				    1 << init_bit_shift);
		switch (w->reg) {
		case CDC_A_TX_1_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX1_CTL,
					    CONN_TX1_SERIAL_TX1_MUX,
					    CONN_TX1_SERIAL_TX1_ADC_1);
			break;
		case CDC_A_TX_2_EN:
		case CDC_A_TX_3_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX2_CTL,
					    CONN_TX2_SERIAL_TX2_MUX,
					    CONN_TX2_SERIAL_TX2_ADC_2);
			break;
		}
		break;
	case SND_SOC_DAPM_POST_PMU:
		/*
		 * Add delay of 12 ms before deasserting the init
		 * to reduce the tx pop
		 */
		usleep_range(12000, 12010);
		snd_soc_component_update_bits(component, adc_reg, 1 << init_bit_shift, 0x00);
		break;
	case SND_SOC_DAPM_POST_PMD:
		switch (w->reg) {
		case CDC_A_TX_1_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX1_CTL,
					    CONN_TX1_SERIAL_TX1_MUX,
					    CONN_TX1_SERIAL_TX1_ZERO);
			break;
		case CDC_A_TX_2_EN:
			snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
					    MICB_1_CTL_CFILT_REF_SEL_MASK, 0);
			/* fall through */
		case CDC_A_TX_3_EN:
			snd_soc_component_update_bits(component, CDC_D_CDC_CONN_TX2_CTL,
					    CONN_TX2_SERIAL_TX2_MUX,
					    CONN_TX2_SERIAL_TX2_ZERO);
			break;
		}


		break;
	}
	return 0;
}