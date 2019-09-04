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
typedef  int /*<<< orphan*/  uint ;
typedef  int u8 ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

__attribute__((used)) static void construct_mic_header1(
                        u8 *mic_header1,
                        sint header_length,
                        u8 *mpdu,
                        uint frtype// add for CONFIG_IEEE80211W, none 11w also can use
                        )
{
_func_enter_;	
    mic_header1[0] = (u8)((header_length - 2) / 256);
    mic_header1[1] = (u8)((header_length - 2) % 256);
#ifdef CONFIG_IEEE80211W
    //802.11w management frame don't AND subtype bits 4,5,6 of frame control field
    if(frtype == WIFI_MGT_TYPE)
		mic_header1[2] = mpdu[0];
	else
#endif //CONFIG_IEEE80211W
		mic_header1[2] = mpdu[0] & 0xcf;    /* Mute CF poll & CF ack bits */
    
    mic_header1[3] = mpdu[1] & 0xc7;    /* Mute retry, more data and pwr mgt bits */
    mic_header1[4] = mpdu[4];       /* A1 */
    mic_header1[5] = mpdu[5];
    mic_header1[6] = mpdu[6];
    mic_header1[7] = mpdu[7];
    mic_header1[8] = mpdu[8];
    mic_header1[9] = mpdu[9];
    mic_header1[10] = mpdu[10];     /* A2 */
    mic_header1[11] = mpdu[11];
    mic_header1[12] = mpdu[12];
    mic_header1[13] = mpdu[13];
    mic_header1[14] = mpdu[14];
    mic_header1[15] = mpdu[15];
_func_exit_;	
}