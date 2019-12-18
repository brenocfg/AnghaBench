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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_version {int dummy; } ;
struct wined3d_shader_src_param {int modifiers; int swizzle; int /*<<< orphan*/  reg; } ;
typedef  enum wined3d_shader_src_modifier { ____Placeholder_wined3d_shader_src_modifier } wined3d_shader_src_modifier ;
typedef  int DWORD ;

/* Variables and functions */
#define  WINED3DSPSM_ABS 141 
#define  WINED3DSPSM_ABSNEG 140 
#define  WINED3DSPSM_BIAS 139 
#define  WINED3DSPSM_BIASNEG 138 
#define  WINED3DSPSM_COMP 137 
#define  WINED3DSPSM_DW 136 
#define  WINED3DSPSM_DZ 135 
#define  WINED3DSPSM_NEG 134 
#define  WINED3DSPSM_NONE 133 
#define  WINED3DSPSM_NOT 132 
#define  WINED3DSPSM_SIGN 131 
#define  WINED3DSPSM_SIGNNEG 130 
#define  WINED3DSPSM_X2 129 
#define  WINED3DSPSM_X2NEG 128 
 int WINED3DSP_NOSWIZZLE ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_dump_register (struct wined3d_string_buffer*,int /*<<< orphan*/ *,struct wined3d_shader_version const*) ; 

__attribute__((used)) static void shader_dump_src_param(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_src_param *param, const struct wined3d_shader_version *shader_version)
{
    enum wined3d_shader_src_modifier src_modifier = param->modifiers;
    DWORD swizzle = param->swizzle;

    if (src_modifier == WINED3DSPSM_NEG
            || src_modifier == WINED3DSPSM_BIASNEG
            || src_modifier == WINED3DSPSM_SIGNNEG
            || src_modifier == WINED3DSPSM_X2NEG
            || src_modifier == WINED3DSPSM_ABSNEG)
        shader_addline(buffer, "-");
    else if (src_modifier == WINED3DSPSM_COMP)
        shader_addline(buffer, "1-");
    else if (src_modifier == WINED3DSPSM_NOT)
        shader_addline(buffer, "!");

    if (src_modifier == WINED3DSPSM_ABS || src_modifier == WINED3DSPSM_ABSNEG)
        shader_addline(buffer, "abs(");

    shader_dump_register(buffer, &param->reg, shader_version);

    switch (src_modifier)
    {
        case WINED3DSPSM_NONE:    break;
        case WINED3DSPSM_NEG:     break;
        case WINED3DSPSM_NOT:     break;
        case WINED3DSPSM_BIAS:    shader_addline(buffer, "_bias"); break;
        case WINED3DSPSM_BIASNEG: shader_addline(buffer, "_bias"); break;
        case WINED3DSPSM_SIGN:    shader_addline(buffer, "_bx2"); break;
        case WINED3DSPSM_SIGNNEG: shader_addline(buffer, "_bx2"); break;
        case WINED3DSPSM_COMP:    break;
        case WINED3DSPSM_X2:      shader_addline(buffer, "_x2"); break;
        case WINED3DSPSM_X2NEG:   shader_addline(buffer, "_x2"); break;
        case WINED3DSPSM_DZ:      shader_addline(buffer, "_dz"); break;
        case WINED3DSPSM_DW:      shader_addline(buffer, "_dw"); break;
        case WINED3DSPSM_ABSNEG:  shader_addline(buffer, ")"); break;
        case WINED3DSPSM_ABS:     shader_addline(buffer, ")"); break;
        default:                  shader_addline(buffer, "_unknown_modifier(%#x)", src_modifier);
    }

    if (swizzle != WINED3DSP_NOSWIZZLE)
    {
        static const char swizzle_chars[] = "xyzw";
        DWORD swizzle_x = swizzle & 0x03;
        DWORD swizzle_y = (swizzle >> 2) & 0x03;
        DWORD swizzle_z = (swizzle >> 4) & 0x03;
        DWORD swizzle_w = (swizzle >> 6) & 0x03;

        if (swizzle_x == swizzle_y
                && swizzle_x == swizzle_z
                && swizzle_x == swizzle_w)
        {
            shader_addline(buffer, ".%c", swizzle_chars[swizzle_x]);
        }
        else
        {
            shader_addline(buffer, ".%c%c%c%c", swizzle_chars[swizzle_x], swizzle_chars[swizzle_y],
                    swizzle_chars[swizzle_z], swizzle_chars[swizzle_w]);
        }
    }
}