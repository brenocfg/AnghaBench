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
typedef  int /*<<< orphan*/  pa_encoding_t ;

/* Variables and functions */
#define  AF_FORMAT_S_AC3 132 
#define  AF_FORMAT_S_DTS 131 
#define  AF_FORMAT_S_DTSHD 130 
#define  AF_FORMAT_S_EAC3 129 
#define  AF_FORMAT_S_MP3 128 
 int /*<<< orphan*/  PA_ENCODING_AC3_IEC61937 ; 
 int /*<<< orphan*/  PA_ENCODING_ANY ; 
 int /*<<< orphan*/  PA_ENCODING_DTS_IEC61937 ; 
 int /*<<< orphan*/  PA_ENCODING_EAC3_IEC61937 ; 
 int /*<<< orphan*/  PA_ENCODING_MPEG_IEC61937 ; 
 int /*<<< orphan*/  PA_ENCODING_PCM ; 
 int /*<<< orphan*/  af_fmt_is_spdif (int) ; 

__attribute__((used)) static pa_encoding_t map_digital_format(int format)
{
    switch (format) {
    case AF_FORMAT_S_AC3:   return PA_ENCODING_AC3_IEC61937;
    case AF_FORMAT_S_EAC3:  return PA_ENCODING_EAC3_IEC61937;
    case AF_FORMAT_S_MP3:   return PA_ENCODING_MPEG_IEC61937;
    case AF_FORMAT_S_DTS:
    case AF_FORMAT_S_DTSHD: return PA_ENCODING_DTS_IEC61937;
#ifdef PA_ENCODING_MPEG2_AAC_IEC61937
    case AF_FORMAT_S_AAC:   return PA_ENCODING_MPEG2_AAC_IEC61937;
#endif
    default:
        if (af_fmt_is_spdif(format))
            return PA_ENCODING_ANY;
        return PA_ENCODING_PCM;
    }
}