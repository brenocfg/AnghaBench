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
struct adapter {int dummy; } ;

/* Variables and functions */
 int EN_AMPDU_RTY_NEW ; 
 int /*<<< orphan*/  REG_ACKTO ; 
 int /*<<< orphan*/  REG_FWHW_TXQ_CTRL ; 
 int rtw_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _InitRetryFunction(struct adapter *padapter)
{
	u8 value8;

	value8 = rtw_read8(padapter, REG_FWHW_TXQ_CTRL);
	value8 |= EN_AMPDU_RTY_NEW;
	rtw_write8(padapter, REG_FWHW_TXQ_CTRL, value8);

	/*  Set ACK timeout */
	rtw_write8(padapter, REG_ACKTO, 0x40);
}