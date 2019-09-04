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
typedef  unsigned char u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned char HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 unsigned char HAL_PRIME_CHNL_OFFSET_LOWER ; 
 unsigned short HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  SetBWMode (struct adapter*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  rtw_hal_set_chan (struct adapter*,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_bw (struct adapter*,unsigned short) ; 
 int /*<<< orphan*/  rtw_set_oper_ch (struct adapter*,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_choffset (struct adapter*,unsigned char) ; 

void set_channel_bwmode(struct adapter *padapter, unsigned char channel, unsigned char channel_offset, unsigned short bwmode)
{
	u8 center_ch;

	if ((bwmode == HT_CHANNEL_WIDTH_20) ||
	    (channel_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)) {
		/* SelectChannel(padapter, channel); */
		center_ch = channel;
	} else {
		/* switch to the proper channel */
		if (channel_offset == HAL_PRIME_CHNL_OFFSET_LOWER) {
			/* SelectChannel(padapter, channel + 2); */
			center_ch = channel + 2;
		} else {
			/* SelectChannel(padapter, channel - 2); */
			center_ch = channel - 2;
		}
	}

	/* set Channel */
	/* saved channel/bw info */
	rtw_set_oper_ch(padapter, channel);
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_chan(padapter, center_ch); /*  set center channel */
	SetBWMode(padapter, bwmode, channel_offset);
}