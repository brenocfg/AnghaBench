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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_hal_set_chan (struct adapter*,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_ch (struct adapter*,unsigned char) ; 

void SelectChannel(struct adapter *padapter, unsigned char channel)
{
	/* saved channel info */
	rtw_set_oper_ch(padapter, channel);
	rtw_hal_set_chan(padapter, channel);
}