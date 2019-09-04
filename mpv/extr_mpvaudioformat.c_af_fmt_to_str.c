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
#define  AF_FORMAT_DOUBLE 144 
#define  AF_FORMAT_DOUBLEP 143 
#define  AF_FORMAT_FLOAT 142 
#define  AF_FORMAT_FLOATP 141 
#define  AF_FORMAT_S16 140 
#define  AF_FORMAT_S16P 139 
#define  AF_FORMAT_S32 138 
#define  AF_FORMAT_S32P 137 
#define  AF_FORMAT_S_AAC 136 
#define  AF_FORMAT_S_AC3 135 
#define  AF_FORMAT_S_DTS 134 
#define  AF_FORMAT_S_DTSHD 133 
#define  AF_FORMAT_S_EAC3 132 
#define  AF_FORMAT_S_MP3 131 
#define  AF_FORMAT_S_TRUEHD 130 
#define  AF_FORMAT_U8 129 
#define  AF_FORMAT_U8P 128 

const char *af_fmt_to_str(int format)
{
    switch (format) {
    case AF_FORMAT_U8:          return "u8";
    case AF_FORMAT_S16:         return "s16";
    case AF_FORMAT_S32:         return "s32";
    case AF_FORMAT_FLOAT:       return "float";
    case AF_FORMAT_DOUBLE:      return "double";
    case AF_FORMAT_U8P:         return "u8p";
    case AF_FORMAT_S16P:        return "s16p";
    case AF_FORMAT_S32P:        return "s32p";
    case AF_FORMAT_FLOATP:      return "floatp";
    case AF_FORMAT_DOUBLEP:     return "doublep";
    case AF_FORMAT_S_AAC:       return "spdif-aac";
    case AF_FORMAT_S_AC3:       return "spdif-ac3";
    case AF_FORMAT_S_DTS:       return "spdif-dts";
    case AF_FORMAT_S_DTSHD:     return "spdif-dtshd";
    case AF_FORMAT_S_EAC3:      return "spdif-eac3";
    case AF_FORMAT_S_MP3:       return "spdif-mp3";
    case AF_FORMAT_S_TRUEHD:    return "spdif-truehd";
    }
    return "??";
}