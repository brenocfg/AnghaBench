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
struct mp_imgfmt_desc {int flags; int component_bits; } ;

/* Variables and functions */
 int IMGFMT_444P ; 
 int MP_IMGFLAG_ALPHA ; 
 int MP_IMGFLAG_RGB ; 
 int MP_IMGFLAG_RGB_P ; 
 int MP_IMGFLAG_YUV_P ; 
 int mp_imgfmt_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int) ; 
 struct mp_imgfmt_desc mp_imgfmt_get_desc (int) ; 
 int /*<<< orphan*/  mp_sws_supported_format (int) ; 

__attribute__((used)) static void get_closest_y444_format(int imgfmt, int *out_format, int *out_bits)
{
    struct mp_imgfmt_desc desc = mp_imgfmt_get_desc(imgfmt);
    int planes = desc.flags & MP_IMGFLAG_ALPHA ? 4 : 3;
    if (desc.flags & MP_IMGFLAG_RGB) {
        // For RGB try to match the amount of bits exactly (but no less than 8, or larger than 16)
        int bits = (desc.component_bits > 8) ? desc.component_bits : 8;
        if (bits > 16)
            bits = 16;
        *out_format = mp_imgfmt_find(0, 0, planes, bits, MP_IMGFLAG_RGB_P);
        if (!mp_sws_supported_format(*out_format))
            *out_format = mp_imgfmt_find(0, 0, planes, 8, MP_IMGFLAG_RGB_P);
    } else if (desc.flags & MP_IMGFLAG_YUV_P) {
        const int bits = (desc.component_bits > 8) ? 16 : 8;
        *out_format = mp_imgfmt_find(0, 0, planes, bits, MP_IMGFLAG_YUV_P);
    } else {
        *out_format = 0;
    }
    if (!mp_sws_supported_format(*out_format))
        *out_format = IMGFMT_444P; // generic fallback
    *out_bits = mp_imgfmt_get_desc(*out_format).component_bits;
}