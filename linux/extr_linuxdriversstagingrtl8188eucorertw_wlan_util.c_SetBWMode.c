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
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_hal_set_bwmode (struct adapter*,int,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_bw (struct adapter*,unsigned short) ; 
 int /*<<< orphan*/  rtw_set_oper_choffset (struct adapter*,unsigned char) ; 

void SetBWMode(struct adapter *padapter, unsigned short bwmode,
	       unsigned char channel_offset)
{
	/* saved bw info */
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_bwmode(padapter, (enum ht_channel_width)bwmode, channel_offset);
}