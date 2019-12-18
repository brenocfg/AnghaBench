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
struct wined3d_shader_src_param {int swizzle; } ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int WINED3DSP_NOSWIZZLE ; 

__attribute__((used)) static void shader_arb_get_swizzle(const struct wined3d_shader_src_param *param, BOOL fixup, char *swizzle_str)
{
    /* For registers of type WINED3DDECLTYPE_D3DCOLOR, data is stored as "bgra",
     * but addressed as "rgba". To fix this we need to swap the register's x
     * and z components. */
    const char *swizzle_chars = fixup ? "zyxw" : "xyzw";
    char *ptr = swizzle_str;

    /* swizzle bits fields: wwzzyyxx */
    DWORD swizzle = param->swizzle;
    DWORD swizzle_x = swizzle & 0x03;
    DWORD swizzle_y = (swizzle >> 2) & 0x03;
    DWORD swizzle_z = (swizzle >> 4) & 0x03;
    DWORD swizzle_w = (swizzle >> 6) & 0x03;

    /* If the swizzle is the default swizzle (ie, "xyzw"), we don't need to
     * generate a swizzle string. Unless we need to our own swizzling. */
    if (swizzle != WINED3DSP_NOSWIZZLE || fixup)
    {
        *ptr++ = '.';
        if (swizzle_x == swizzle_y && swizzle_x == swizzle_z && swizzle_x == swizzle_w) {
            *ptr++ = swizzle_chars[swizzle_x];
        } else {
            *ptr++ = swizzle_chars[swizzle_x];
            *ptr++ = swizzle_chars[swizzle_y];
            *ptr++ = swizzle_chars[swizzle_z];
            *ptr++ = swizzle_chars[swizzle_w];
        }
    }

    *ptr = '\0';
}