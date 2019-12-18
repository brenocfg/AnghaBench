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

/* Variables and functions */
 int IEC958_AES3_CON_FS_176400 ; 
 int IEC958_AES3_CON_FS_192000 ; 
 int IEC958_AES3_CON_FS_22050 ; 
 int IEC958_AES3_CON_FS_24000 ; 
 int IEC958_AES3_CON_FS_32000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 int IEC958_AES3_CON_FS_768000 ; 
 int IEC958_AES3_CON_FS_88200 ; 
 int IEC958_AES3_CON_FS_96000 ; 
 int IEC958_AES3_CON_FS_NOTID ; 

__attribute__((used)) static int map_iec958_srate(int srate)
{
    switch (srate) {
    case 44100:     return IEC958_AES3_CON_FS_44100;
    case 48000:     return IEC958_AES3_CON_FS_48000;
    case 32000:     return IEC958_AES3_CON_FS_32000;
    case 22050:     return IEC958_AES3_CON_FS_22050;
    case 24000:     return IEC958_AES3_CON_FS_24000;
    case 88200:     return IEC958_AES3_CON_FS_88200;
    case 768000:    return IEC958_AES3_CON_FS_768000;
    case 96000:     return IEC958_AES3_CON_FS_96000;
    case 176400:    return IEC958_AES3_CON_FS_176400;
    case 192000:    return IEC958_AES3_CON_FS_192000;
    default:        return IEC958_AES3_CON_FS_NOTID;
    }
}