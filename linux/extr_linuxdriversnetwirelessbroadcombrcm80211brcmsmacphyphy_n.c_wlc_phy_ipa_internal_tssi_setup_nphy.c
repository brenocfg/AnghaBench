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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ phy_corenum; int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_MASTER1 ; 
 int /*<<< orphan*/  IQCAL_IDAC ; 
 int /*<<< orphan*/  IQCAL_VCM_HG ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2056 ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 int /*<<< orphan*/  RESERVED_ADDR30 ; 
 int /*<<< orphan*/  RESERVED_ADDR31 ; 
 int /*<<< orphan*/  TSSIA ; 
 int /*<<< orphan*/  TSSIG ; 
 int /*<<< orphan*/  TSSI_MISC1 ; 
 int /*<<< orphan*/  TSSI_MISC2 ; 
 int /*<<< orphan*/  TSSI_MISC3 ; 
 int /*<<< orphan*/  TSSI_VCM ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TX_AMP_DET ; 
 int /*<<< orphan*/  TX_SSI_MASTER ; 
 int /*<<< orphan*/  TX_SSI_MUX ; 
 int /*<<< orphan*/  WRITE_RADIO_REG2 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_RADIO_SYN (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wlc_phy_ipa_internal_tssi_setup_nphy(struct brcms_phy *pi)
{
	u8 core;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		for (core = 0; core < pi->pubpi.phy_corenum; core++) {
			if (CHSPEC_IS2G(pi->radio_chanspec)) {
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MASTER, 0x5);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MUX, 0xe);

				if (pi->pubpi.radiorev != 5)
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TSSIA, 0);

				if (!NREV_IS(pi->pubpi.phy_rev, 7))
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TSSIG, 0x1);
				else
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TSSIG, 0x31);
			} else {
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MASTER, 0x9);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MUX, 0xc);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSIG, 0);

				if (pi->pubpi.radiorev != 5) {
					if (!NREV_IS(pi->pubpi.phy_rev, 7))
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIA, 0x1);
					else
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIA, 0x31);
				}
			}
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core, IQCAL_VCM_HG,
					 0);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core, IQCAL_IDAC,
					 0);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core, TSSI_VCM,
					 0x3);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core, TSSI_MISC1,
					 0x0);
		}
	} else {
		WRITE_RADIO_SYN(pi, RADIO_2056, RESERVED_ADDR31,
				(CHSPEC_IS2G(pi->radio_chanspec)) ? 0x128 :
				0x80);
		WRITE_RADIO_SYN(pi, RADIO_2056, RESERVED_ADDR30, 0x0);
		WRITE_RADIO_SYN(pi, RADIO_2056, GPIO_MASTER1, 0x29);

		for (core = 0; core < pi->pubpi.phy_corenum; core++) {
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, IQCAL_VCM_HG,
					 0x0);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, IQCAL_IDAC,
					 0x0);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, TSSI_VCM,
					 0x3);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, TX_AMP_DET,
					 0x0);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, TSSI_MISC1,
					 0x8);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, TSSI_MISC2,
					 0x0);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core, TSSI_MISC3,
					 0x0);

			if (CHSPEC_IS2G(pi->radio_chanspec)) {
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TX_SSI_MASTER, 0x5);

				if (pi->pubpi.radiorev != 5)
					WRITE_RADIO_REG2(pi, RADIO_2056, TX,
							 core, TSSIA, 0x0);
				if (NREV_GE(pi->pubpi.phy_rev, 5))
					WRITE_RADIO_REG2(pi, RADIO_2056, TX,
							 core, TSSIG, 0x31);
				else
					WRITE_RADIO_REG2(pi, RADIO_2056, TX,
							 core, TSSIG, 0x11);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TX_SSI_MUX, 0xe);
			} else {
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TX_SSI_MASTER, 0x9);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TSSIA, 0x31);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TSSIG, 0x0);
				WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
						 TX_SSI_MUX, 0xc);
			}
		}
	}
}