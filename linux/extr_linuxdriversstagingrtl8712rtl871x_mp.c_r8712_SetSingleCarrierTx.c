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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bBBResetB ; 
 int /*<<< orphan*/  bCCKBBMode ; 
 int /*<<< orphan*/  bCCKScramble ; 
 int bDisable ; 
 int bEnable ; 
 int /*<<< orphan*/  bOFDMContinueTx ; 
 int /*<<< orphan*/  bOFDMEn ; 
 int /*<<< orphan*/  bOFDMSingleCarrier ; 
 int /*<<< orphan*/  bOFDMSingleTone ; 
 int /*<<< orphan*/  get_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rCCK0_System ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  rOFDM1_LSTF ; 
 int /*<<< orphan*/  rPMAC_Reset ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void r8712_SetSingleCarrierTx(struct _adapter *pAdapter, u8 bStart)
{
	if (bStart) { /* Start Single Carrier. */
		/* 1. if OFDM block on? */
		if (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn))
			/*set OFDM block on*/
			set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		/* 2. set CCK test mode off, set to CCK normal mode */
		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, bDisable);
		/* 3. turn on scramble setting */
		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
		/* 4. Turn On Single Carrier Tx and off the other test modes. */
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bEnable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
	} else { /* Stop Single Carrier.*/
		/* Turn off all test modes.*/
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier,
			   bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
		msleep(20);
		/*BB Reset*/
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	}
}