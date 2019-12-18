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
struct wined3d_gl_info {scalar_t__ glsl_version; } ;

/* Variables and functions */
 scalar_t__ MAKEDWORD_VERSION (int,int) ; 

__attribute__((used)) static unsigned int shader_glsl_get_version(const struct wined3d_gl_info *gl_info)
{
    if (gl_info->glsl_version >= MAKEDWORD_VERSION(4, 40))
        return 440;
    else if (gl_info->glsl_version >= MAKEDWORD_VERSION(1, 50))
        return 150;
    else if (gl_info->glsl_version >= MAKEDWORD_VERSION(1, 30))
        return 130;
    else
        return 120;
}