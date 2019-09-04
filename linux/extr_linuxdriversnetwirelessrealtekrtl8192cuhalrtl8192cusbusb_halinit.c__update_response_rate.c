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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 scalar_t__ REG_INIRTS_RATE_SEL ; 
 scalar_t__ REG_RRSR ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 

void _update_response_rate(_adapter *padapter,unsigned int mask)
{
	u8	RateIndex = 0;
	// Set RRSR rate table.
	rtw_write8(padapter, REG_RRSR, mask&0xff);
	rtw_write8(padapter,REG_RRSR+1, (mask>>8)&0xff);
	

	// Set RTS initial rate
	while(mask > 0x1)
	{
		mask = (mask>> 1);
		RateIndex++;
	}
	rtw_write8(padapter, REG_INIRTS_RATE_SEL, RateIndex);
}