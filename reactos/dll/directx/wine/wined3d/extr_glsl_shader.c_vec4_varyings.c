#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int glsl_varyings; } ;
struct wined3d_gl_info {int quirks; TYPE_1__ limits; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3D_QUIRK_GLSL_CLIP_VARYING ; 

__attribute__((used)) static unsigned int vec4_varyings(DWORD shader_major, const struct wined3d_gl_info *gl_info)
{
    unsigned int ret = gl_info->limits.glsl_varyings / 4;
    /* 4.0 shaders do not write clip coords because d3d10 does not support user clipplanes */
    if(shader_major > 3) return ret;

    /* 3.0 shaders may need an extra varying for the clip coord on some cards(mostly dx10 ones) */
    if (gl_info->quirks & WINED3D_QUIRK_GLSL_CLIP_VARYING) ret -= 1;
    return ret;
}