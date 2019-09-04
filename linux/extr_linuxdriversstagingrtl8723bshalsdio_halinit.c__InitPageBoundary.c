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
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_TRXFF_BNDY ; 
 int /*<<< orphan*/  RX_DMA_BOUNDARY_8723B ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitPageBoundary(struct adapter *padapter)
{
	/*  RX Page Boundary */
	u16 rxff_bndy = RX_DMA_BOUNDARY_8723B;

	rtw_write16(padapter, (REG_TRXFF_BNDY + 2), rxff_bndy);
}