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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bTxAGCRateCCK ; 
 int /*<<< orphan*/  rTxAGC_CCK_Mcs32 ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetCCKTxPower(struct _adapter *pAdapter, u8 TxPower)
{
	u16 TxAGC = 0;

	TxAGC = TxPower;
	set_bb_reg(pAdapter, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
}