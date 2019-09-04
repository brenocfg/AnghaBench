#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct adm8211_priv* priv; } ;
struct adm8211_priv {int ant_power; int tx_power; int lpf_cutoff; int lnags_threshold; int transceiver_type; scalar_t__ bbp_type; TYPE_2__* eeprom; TYPE_1__* pdev; } ;
struct TYPE_4__ {int* antenna_power; int* tx_power; int* lpf_cutoff; int* lnags_threshold; int cr28; int cr29; int /*<<< orphan*/  cr49; } ;
struct TYPE_3__ {scalar_t__ revision; } ;

/* Variables and functions */
#define  ADM8211_AL2210L 132 
 int ADM8211_CSR_GPIO_EN0 ; 
 int ADM8211_CSR_GPIO_O0 ; 
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADM8211_IDLE () ; 
#define  ADM8211_MAX2820 131 
 int /*<<< orphan*/  ADM8211_RESTORE () ; 
 scalar_t__ ADM8211_REV_BA ; 
 scalar_t__ ADM8211_REV_CA ; 
#define  ADM8211_RFMD2948 130 
#define  ADM8211_RFMD2958 129 
#define  ADM8211_RFMD2958_RF3000_CONTROL_POWER 128 
 int ADM8211_SYNRF_PE1 ; 
 int ADM8211_SYNRF_PHYRST ; 
 int ADM8211_SYNRF_SELRF ; 
 scalar_t__ ADM8211_TYPE_ADMTEK ; 
 scalar_t__ ADM8211_TYPE_RFMD ; 
 int /*<<< orphan*/  CAP0 ; 
 int /*<<< orphan*/  GPIO ; 
 int /*<<< orphan*/  PLCPHD ; 
 int RF3000_HIGH_GAIN_CALIB ; 
 int RF3000_LOW_GAIN_CALIB ; 
 int RF3000_TX_VAR_GAIN__TX_LEN_EXT ; 
 int /*<<< orphan*/  SI4126_IF_N_DIV ; 
 int /*<<< orphan*/  SI4126_IF_R_DIV ; 
 int /*<<< orphan*/  SI4126_MAIN_CONF ; 
 int SI4126_MAIN_XINDIV2 ; 
 int /*<<< orphan*/  SI4126_PHASE_DET_GAIN ; 
 int /*<<< orphan*/  SI4126_POWERDOWN ; 
 int SI4126_POWERDOWN_PDIB ; 
 int SI4126_POWERDOWN_PDRB ; 
 int /*<<< orphan*/  SI4126_RF2_N_DIV ; 
 int /*<<< orphan*/  SI4126_RF2_R_DIV ; 
 int /*<<< orphan*/  SYNRF ; 
 int /*<<< orphan*/  adm8211_rf_write_syn_al2210l (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  adm8211_rf_write_syn_max2820 (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  adm8211_rf_write_syn_rfmd2948 (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adm8211_rf_write_syn_rfmd2958 (struct ieee80211_hw*,int,int const) ; 
 int /*<<< orphan*/  adm8211_write_bbp (struct ieee80211_hw*,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int adm8211_rf_set_channel(struct ieee80211_hw *dev, unsigned int chan)
{
	static const u32 adm8211_rfmd2958_reg5[] =
		{0x22BD, 0x22D2, 0x22E8, 0x22FE, 0x2314, 0x232A, 0x2340,
		 0x2355, 0x236B, 0x2381, 0x2397, 0x23AD, 0x23C2, 0x23F7};
	static const u32 adm8211_rfmd2958_reg6[] =
		{0x05D17, 0x3A2E8, 0x2E8BA, 0x22E8B, 0x1745D, 0x0BA2E, 0x00000,
		 0x345D1, 0x28BA2, 0x1D174, 0x11745, 0x05D17, 0x3A2E8, 0x11745};

	struct adm8211_priv *priv = dev->priv;
	u8 ant_power = priv->ant_power > 0x3F ?
		priv->eeprom->antenna_power[chan - 1] : priv->ant_power;
	u8 tx_power = priv->tx_power > 0x3F ?
		priv->eeprom->tx_power[chan - 1] : priv->tx_power;
	u8 lpf_cutoff = priv->lpf_cutoff == 0xFF ?
		priv->eeprom->lpf_cutoff[chan - 1] : priv->lpf_cutoff;
	u8 lnags_thresh = priv->lnags_threshold == 0xFF ?
		priv->eeprom->lnags_threshold[chan - 1] : priv->lnags_threshold;
	u32 reg;

	ADM8211_IDLE();

	/* Program synthesizer to new channel */
	switch (priv->transceiver_type) {
	case ADM8211_RFMD2958:
	case ADM8211_RFMD2958_RF3000_CONTROL_POWER:
		adm8211_rf_write_syn_rfmd2958(dev, 0x00, 0x04007);
		adm8211_rf_write_syn_rfmd2958(dev, 0x02, 0x00033);

		adm8211_rf_write_syn_rfmd2958(dev, 0x05,
			adm8211_rfmd2958_reg5[chan - 1]);
		adm8211_rf_write_syn_rfmd2958(dev, 0x06,
			adm8211_rfmd2958_reg6[chan - 1]);
		break;

	case ADM8211_RFMD2948:
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_MAIN_CONF,
					      SI4126_MAIN_XINDIV2);
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_POWERDOWN,
					      SI4126_POWERDOWN_PDIB |
					      SI4126_POWERDOWN_PDRB);
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_PHASE_DET_GAIN, 0);
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_RF2_N_DIV,
					      (chan == 14 ?
					       2110 : (2033 + (chan * 5))));
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_IF_N_DIV, 1496);
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_RF2_R_DIV, 44);
		adm8211_rf_write_syn_rfmd2948(dev, SI4126_IF_R_DIV, 44);
		break;

	case ADM8211_MAX2820:
		adm8211_rf_write_syn_max2820(dev, 0x3,
			(chan == 14 ? 0x054 : (0x7 + (chan * 5))));
		break;

	case ADM8211_AL2210L:
		adm8211_rf_write_syn_al2210l(dev, 0x0,
			(chan == 14 ? 0x229B4 : (0x22967 + (chan * 5))));
		break;

	default:
		wiphy_debug(dev->wiphy, "unsupported transceiver type %d\n",
			    priv->transceiver_type);
		break;
	}

	/* write BBP regs */
	if (priv->bbp_type == ADM8211_TYPE_RFMD) {

	/* SMC 2635W specific? adm8211b doesn't use the 2948 though.. */
	/* TODO: remove if SMC 2635W doesn't need this */
	if (priv->transceiver_type == ADM8211_RFMD2948) {
		reg = ADM8211_CSR_READ(GPIO);
		reg &= 0xfffc0000;
		reg |= ADM8211_CSR_GPIO_EN0;
		if (chan != 14)
			reg |= ADM8211_CSR_GPIO_O0;
		ADM8211_CSR_WRITE(GPIO, reg);
	}

	if (priv->transceiver_type == ADM8211_RFMD2958) {
		/* set PCNT2 */
		adm8211_rf_write_syn_rfmd2958(dev, 0x0B, 0x07100);
		/* set PCNT1 P_DESIRED/MID_BIAS */
		reg = le16_to_cpu(priv->eeprom->cr49);
		reg >>= 13;
		reg <<= 15;
		reg |= ant_power << 9;
		adm8211_rf_write_syn_rfmd2958(dev, 0x0A, reg);
		/* set TXRX TX_GAIN */
		adm8211_rf_write_syn_rfmd2958(dev, 0x09, 0x00050 |
			(priv->pdev->revision < ADM8211_REV_CA ? tx_power : 0));
	} else {
		reg = ADM8211_CSR_READ(PLCPHD);
		reg &= 0xff00ffff;
		reg |= tx_power << 18;
		ADM8211_CSR_WRITE(PLCPHD, reg);
	}

	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_SELRF |
			  ADM8211_SYNRF_PE1 | ADM8211_SYNRF_PHYRST);
	ADM8211_CSR_READ(SYNRF);
	msleep(30);

	/* RF3000 BBP */
	if (priv->transceiver_type != ADM8211_RFMD2958)
		adm8211_write_bbp(dev, RF3000_TX_VAR_GAIN__TX_LEN_EXT,
				  tx_power<<2);
	adm8211_write_bbp(dev, RF3000_LOW_GAIN_CALIB, lpf_cutoff);
	adm8211_write_bbp(dev, RF3000_HIGH_GAIN_CALIB, lnags_thresh);
	adm8211_write_bbp(dev, 0x1c, priv->pdev->revision == ADM8211_REV_BA ?
				     priv->eeprom->cr28 : 0);
	adm8211_write_bbp(dev, 0x1d, priv->eeprom->cr29);

	ADM8211_CSR_WRITE(SYNRF, 0);

	/* Nothing to do for ADMtek BBP */
	} else if (priv->bbp_type != ADM8211_TYPE_ADMTEK)
		wiphy_debug(dev->wiphy, "unsupported BBP type %d\n",
			    priv->bbp_type);

	ADM8211_RESTORE();

	/* update current channel for adhoc (and maybe AP mode) */
	reg = ADM8211_CSR_READ(CAP0);
	reg &= ~0xF;
	reg |= chan;
	ADM8211_CSR_WRITE(CAP0, reg);

	return 0;
}