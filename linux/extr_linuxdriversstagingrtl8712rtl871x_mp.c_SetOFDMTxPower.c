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
typedef  int u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bTxAGCRate18_06 ; 
 int /*<<< orphan*/  bTxAGCRate54_24 ; 
 int /*<<< orphan*/  bTxAGCRateMCS11_MCS8 ; 
 int /*<<< orphan*/  bTxAGCRateMCS15_MCS12 ; 
 int /*<<< orphan*/  bTxAGCRateMCS3_MCS0 ; 
 int /*<<< orphan*/  bTxAGCRateMCS7_MCS4 ; 
 int /*<<< orphan*/  rTxAGC_Mcs03_Mcs00 ; 
 int /*<<< orphan*/  rTxAGC_Mcs07_Mcs04 ; 
 int /*<<< orphan*/  rTxAGC_Mcs11_Mcs08 ; 
 int /*<<< orphan*/  rTxAGC_Mcs15_Mcs12 ; 
 int /*<<< orphan*/  rTxAGC_Rate18_06 ; 
 int /*<<< orphan*/  rTxAGC_Rate54_24 ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetOFDMTxPower(struct _adapter *pAdapter, u8 TxPower)
{
	u32 TxAGC = 0;

	TxAGC |= ((TxPower << 24) | (TxPower << 16) | (TxPower << 8) |
		  TxPower);
	set_bb_reg(pAdapter, rTxAGC_Rate18_06, bTxAGCRate18_06, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Rate54_24, bTxAGCRate54_24, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs03_Mcs00, bTxAGCRateMCS3_MCS0, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs07_Mcs04, bTxAGCRateMCS7_MCS4, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs11_Mcs08, bTxAGCRateMCS11_MCS8, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs15_Mcs12, bTxAGCRateMCS15_MCS12, TxAGC);
}