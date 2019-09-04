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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  curr_txpoweridx; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetCCKTxPower (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetOFDMTxPower (struct _adapter*,int /*<<< orphan*/ ) ; 

void r8712_SetTxPower(struct _adapter *pAdapter)
{
	u8 TxPower = pAdapter->mppriv.curr_txpoweridx;

	SetCCKTxPower(pAdapter, TxPower);
	SetOFDMTxPower(pAdapter, TxPower);
}