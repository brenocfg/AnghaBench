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

__attribute__((used)) static void construct_ctr_preload(
                        u8 *ctr_preload,
                        sint a4_exists,
                        sint qc_exists,
                        u8 *mpdu,
                        u8 *pn_vector,
                        sint c,
                        uint frtype // add for CONFIG_IEEE80211W, none 11w also can use
                        )
{
    sint i = 0;
_func_enter_;		
    for (i=0; i<16; i++) ctr_preload[i] = 0x00;
    i = 0;
	
    ctr_preload[0] = 0x01;                                  /* flag */
    if (qc_exists && a4_exists) 
		ctr_preload[1] = mpdu[30] & 0x0f;   /* QoC_Control */
    if (qc_exists && !a4_exists) 
		ctr_preload[1] = mpdu[24] & 0x0f;
#ifdef CONFIG_IEEE80211W
	//802.11w management frame should set management bit(4)
	if(frtype == WIFI_MGT_TYPE)
		ctr_preload[1] |= BIT(4);
#endif //CONFIG_IEEE80211W
    for (i = 2; i < 8; i++)
        ctr_preload[i] = mpdu[i + 8];                       /* ctr_preload[2:7] = A2[0:5] = mpdu[10:15] */
    #ifdef CONSISTENT_PN_ORDER
      for (i = 8; i < 14; i++)
            ctr_preload[i] =    pn_vector[i - 8];           /* ctr_preload[8:13] = PN[0:5] */
    #else
      for (i = 8; i < 14; i++)
            ctr_preload[i] =    pn_vector[13 - i];          /* ctr_preload[8:13] = PN[5:0] */
    #endif
    ctr_preload[14] =  (unsigned char) (c / 256); /* Ctr */
    ctr_preload[15] =  (unsigned char) (c % 256);
_func_exit_;		
}