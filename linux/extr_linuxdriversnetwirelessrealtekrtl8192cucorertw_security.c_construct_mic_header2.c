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
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

__attribute__((used)) static void construct_mic_header2(
                u8 *mic_header2,
                u8 *mpdu,
                sint a4_exists,
                sint qc_exists
                )
{
    sint i;
_func_enter_;	
    for (i = 0; i<16; i++) mic_header2[i]=0x00;

    mic_header2[0] = mpdu[16];    /* A3 */
    mic_header2[1] = mpdu[17];
    mic_header2[2] = mpdu[18];
    mic_header2[3] = mpdu[19];
    mic_header2[4] = mpdu[20];
    mic_header2[5] = mpdu[21];

    //mic_header2[6] = mpdu[22] & 0xf0;   /* SC */
    mic_header2[6] = 0x00;
    mic_header2[7] = 0x00; /* mpdu[23]; */


    if (!qc_exists && a4_exists)
    {
        for (i=0;i<6;i++) mic_header2[8+i] = mpdu[24+i];   /* A4 */

    }

    if (qc_exists && !a4_exists)
    {
        mic_header2[8] = mpdu[24] & 0x0f; /* mute bits 15 - 4 */
        mic_header2[9] = mpdu[25] & 0x00;
    }

    if (qc_exists && a4_exists)
    {
        for (i=0;i<6;i++) mic_header2[8+i] = mpdu[24+i];   /* A4 */

        mic_header2[14] = mpdu[30] & 0x0f;
        mic_header2[15] = mpdu[31] & 0x00;
    }

_func_exit_;	
}