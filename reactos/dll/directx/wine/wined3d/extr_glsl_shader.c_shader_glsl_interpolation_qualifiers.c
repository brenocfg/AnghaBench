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
typedef  enum wined3d_shader_interpolation_mode { ____Placeholder_wined3d_shader_interpolation_mode } wined3d_shader_interpolation_mode ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3DSIM_CONSTANT 131 
#define  WINED3DSIM_LINEAR 130 
#define  WINED3DSIM_LINEAR_NOPERSPECTIVE 129 
#define  WINED3DSIM_NONE 128 

__attribute__((used)) static const char *shader_glsl_interpolation_qualifiers(enum wined3d_shader_interpolation_mode mode)
{
    switch (mode)
    {
        case WINED3DSIM_CONSTANT:
            return "flat";
        case WINED3DSIM_LINEAR_NOPERSPECTIVE:
            return "noperspective";
        default:
            FIXME("Unhandled interpolation mode %#x.\n", mode);
        case WINED3DSIM_NONE:
        case WINED3DSIM_LINEAR:
            return "";
    }
}