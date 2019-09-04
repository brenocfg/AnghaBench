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
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int _TXDMA_BEQ_MAP (int) ; 
 int _TXDMA_BKQ_MAP (int) ; 
 int _TXDMA_HIQ_MAP (int) ; 
 int _TXDMA_MGQ_MAP (int) ; 
 int _TXDMA_VIQ_MAP (int) ; 
 int _TXDMA_VOQ_MAP (int) ; 
 int usb_read16 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _InitNormalChipRegPriority(struct adapter *Adapter, u16 beQ,
				       u16 bkQ, u16 viQ, u16 voQ, u16 mgtQ,
				       u16 hiQ)
{
	u16 value16	= (usb_read16(Adapter, REG_TRXDMA_CTRL) & 0x7);

	value16 |= _TXDMA_BEQ_MAP(beQ)	| _TXDMA_BKQ_MAP(bkQ) |
		   _TXDMA_VIQ_MAP(viQ)	| _TXDMA_VOQ_MAP(voQ) |
		   _TXDMA_MGQ_MAP(mgtQ) | _TXDMA_HIQ_MAP(hiQ);

	usb_write16(Adapter, REG_TRXDMA_CTRL, value16);
}