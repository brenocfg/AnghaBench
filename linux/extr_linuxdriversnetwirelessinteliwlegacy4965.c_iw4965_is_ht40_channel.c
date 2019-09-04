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
typedef  int __le32 ;

/* Variables and functions */
 int CHANNEL_MODE_MIXED ; 
 int CHANNEL_MODE_PURE_40 ; 
 int RXON_FLG_CHANNEL_MODE_MSK ; 
 int RXON_FLG_CHANNEL_MODE_POS ; 
 int le32_to_cpu (int) ; 

__attribute__((used)) static bool
iw4965_is_ht40_channel(__le32 rxon_flags)
{
	int chan_mod =
	    le32_to_cpu(rxon_flags & RXON_FLG_CHANNEL_MODE_MSK) >>
	    RXON_FLG_CHANNEL_MODE_POS;
	return (chan_mod == CHANNEL_MODE_PURE_40 ||
		chan_mod == CHANNEL_MODE_MIXED);
}