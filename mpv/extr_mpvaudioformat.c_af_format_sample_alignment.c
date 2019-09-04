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
#define  AF_FORMAT_S_AAC 134 
#define  AF_FORMAT_S_AC3 133 
#define  AF_FORMAT_S_DTS 132 
#define  AF_FORMAT_S_DTSHD 131 
#define  AF_FORMAT_S_EAC3 130 
#define  AF_FORMAT_S_MP3 129 
#define  AF_FORMAT_S_TRUEHD 128 

int af_format_sample_alignment(int format)
{
    switch (format) {
    case AF_FORMAT_S_AAC:       return 16384 / 4;
    case AF_FORMAT_S_AC3:       return 6144 / 4;
    case AF_FORMAT_S_DTSHD:     return 32768 / 16;
    case AF_FORMAT_S_DTS:       return 2048 / 4;
    case AF_FORMAT_S_EAC3:      return 24576 / 4;
    case AF_FORMAT_S_MP3:       return 4608 / 4;
    case AF_FORMAT_S_TRUEHD:    return 61440 / 16;
    default:                    return 1;
    }
}