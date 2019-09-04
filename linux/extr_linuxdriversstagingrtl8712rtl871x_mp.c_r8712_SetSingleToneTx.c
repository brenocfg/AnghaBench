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
struct TYPE_2__ {int antenna_tx; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
#define  ANTENNA_A 129 
#define  ANTENNA_B 128 
 int /*<<< orphan*/  RF_AC ; 
 scalar_t__ RF_PATH_A ; 
 scalar_t__ RF_PATH_B ; 
 int /*<<< orphan*/  RF_TX_G2 ; 
 int /*<<< orphan*/  bCCKEn ; 
 int /*<<< orphan*/  bDisable ; 
 int /*<<< orphan*/  bEnable ; 
 int /*<<< orphan*/  bOFDMEn ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rf_reg (struct _adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void r8712_SetSingleToneTx(struct _adapter *pAdapter, u8 bStart)
{
	u8 rfPath;

	switch (pAdapter->mppriv.antenna_tx) {
	case ANTENNA_B:
		rfPath = RF_PATH_B;
		break;
	case ANTENNA_A:
	default:
		rfPath = RF_PATH_A;
		break;
	}
	if (bStart) { /* Start Single Tone.*/
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bDisable);
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bDisable);
		set_rf_reg(pAdapter, rfPath, RF_TX_G2, bRFRegOffsetMask,
			   0xd4000);
		msleep(100);
		/* PAD all on.*/
		set_rf_reg(pAdapter, rfPath, RF_AC, bRFRegOffsetMask, 0x2001f);
		msleep(100);
	} else { /* Stop Single Tone.*/
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bEnable);
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		set_rf_reg(pAdapter, rfPath, RF_TX_G2, bRFRegOffsetMask,
			   0x54000);
		msleep(100);
		/* PAD all on.*/
		set_rf_reg(pAdapter, rfPath, RF_AC, bRFRegOffsetMask, 0x30000);
		msleep(100);
	}
}