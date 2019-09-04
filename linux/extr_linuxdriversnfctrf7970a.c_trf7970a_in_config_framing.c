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
typedef  scalar_t__ u8 ;
struct trf7970a {scalar_t__ iso_ctrl_tech; int framing; scalar_t__ chip_status_ctrl; scalar_t__ iso_ctrl; scalar_t__ modulator_sys_clk_ctrl; scalar_t__ guard_time; int /*<<< orphan*/  dev; void* tx_cmd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  NFC_DIGITAL_FRAMING_ISO15693_INVENTORY 140 
#define  NFC_DIGITAL_FRAMING_ISO15693_T5T 139 
#define  NFC_DIGITAL_FRAMING_NFCA_NFC_DEP 138 
#define  NFC_DIGITAL_FRAMING_NFCA_SHORT 137 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD 136 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A 135 
#define  NFC_DIGITAL_FRAMING_NFCA_T2T 134 
#define  NFC_DIGITAL_FRAMING_NFCA_T4T 133 
#define  NFC_DIGITAL_FRAMING_NFCB 132 
#define  NFC_DIGITAL_FRAMING_NFCB_T4T 131 
#define  NFC_DIGITAL_FRAMING_NFCF 130 
#define  NFC_DIGITAL_FRAMING_NFCF_NFC_DEP 129 
#define  NFC_DIGITAL_FRAMING_NFCF_T3T 128 
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_CTRL ; 
 scalar_t__ TRF7970A_CHIP_STATUS_RF_ON ; 
 void* TRF7970A_CMD_TRANSMIT ; 
 void* TRF7970A_CMD_TRANSMIT_NO_CRC ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL ; 
 scalar_t__ TRF7970A_ISO_CTRL_RX_CRC_N ; 
 int /*<<< orphan*/  TRF7970A_MODULATOR_SYS_CLK_CTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int trf7970a_is_rf_field (struct trf7970a*,int*) ; 
 int trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int trf7970a_in_config_framing(struct trf7970a *trf, int framing)
{
	u8 iso_ctrl = trf->iso_ctrl_tech;
	bool is_rf_field = false;
	int ret;

	dev_dbg(trf->dev, "framing: %d\n", framing);

	switch (framing) {
	case NFC_DIGITAL_FRAMING_NFCA_SHORT:
	case NFC_DIGITAL_FRAMING_NFCA_STANDARD:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT_NO_CRC;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	case NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
	case NFC_DIGITAL_FRAMING_NFCA_T4T:
	case NFC_DIGITAL_FRAMING_NFCB:
	case NFC_DIGITAL_FRAMING_NFCB_T4T:
	case NFC_DIGITAL_FRAMING_NFCF:
	case NFC_DIGITAL_FRAMING_NFCF_T3T:
	case NFC_DIGITAL_FRAMING_ISO15693_INVENTORY:
	case NFC_DIGITAL_FRAMING_ISO15693_T5T:
	case NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
	case NFC_DIGITAL_FRAMING_NFCF_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	case NFC_DIGITAL_FRAMING_NFCA_T2T:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	default:
		dev_dbg(trf->dev, "Unsupported Framing: %d\n", framing);
		return -EINVAL;
	}

	trf->framing = framing;

	if (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) {
		ret = trf7970a_is_rf_field(trf, &is_rf_field);
		if (ret)
			return ret;

		if (is_rf_field)
			return -EBUSY;
	}

	if (iso_ctrl != trf->iso_ctrl) {
		ret = trf7970a_write(trf, TRF7970A_ISO_CTRL, iso_ctrl);
		if (ret)
			return ret;

		trf->iso_ctrl = iso_ctrl;

		ret = trf7970a_write(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
				     trf->modulator_sys_clk_ctrl);
		if (ret)
			return ret;
	}

	if (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) {
		ret = trf7970a_write(trf, TRF7970A_CHIP_STATUS_CTRL,
				     trf->chip_status_ctrl |
				     TRF7970A_CHIP_STATUS_RF_ON);
		if (ret)
			return ret;

		trf->chip_status_ctrl |= TRF7970A_CHIP_STATUS_RF_ON;

		usleep_range(trf->guard_time, trf->guard_time + 1000);
	}

	return 0;
}