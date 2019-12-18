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
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ WINED3DTA_CURRENT ; 
 scalar_t__ WINED3DTA_DIFFUSE ; 
 scalar_t__ WINED3DTA_TEXTURE ; 
 scalar_t__ WINED3DTA_TFACTOR ; 
#define  WINED3D_TOP_ADD 152 
#define  WINED3D_TOP_ADD_SIGNED 151 
#define  WINED3D_TOP_ADD_SIGNED_2X 150 
#define  WINED3D_TOP_ADD_SMOOTH 149 
#define  WINED3D_TOP_BLEND_CURRENT_ALPHA 148 
#define  WINED3D_TOP_BLEND_DIFFUSE_ALPHA 147 
#define  WINED3D_TOP_BLEND_FACTOR_ALPHA 146 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA 145 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM 144 
#define  WINED3D_TOP_BUMPENVMAP 143 
#define  WINED3D_TOP_BUMPENVMAP_LUMINANCE 142 
#define  WINED3D_TOP_DISABLE 141 
#define  WINED3D_TOP_DOTPRODUCT3 140 
#define  WINED3D_TOP_LERP 139 
#define  WINED3D_TOP_MODULATE 138 
#define  WINED3D_TOP_MODULATE_2X 137 
#define  WINED3D_TOP_MODULATE_4X 136 
#define  WINED3D_TOP_MODULATE_ALPHA_ADD_COLOR 135 
#define  WINED3D_TOP_MODULATE_COLOR_ADD_ALPHA 134 
#define  WINED3D_TOP_MODULATE_INVALPHA_ADD_COLOR 133 
#define  WINED3D_TOP_MODULATE_INVCOLOR_ADD_ALPHA 132 
#define  WINED3D_TOP_MULTIPLY_ADD 131 
#define  WINED3D_TOP_SELECT_ARG1 130 
#define  WINED3D_TOP_SELECT_ARG2 129 
#define  WINED3D_TOP_SUBTRACT 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,char const*,char const*,char const*,...) ; 
 char* shader_glsl_get_ffp_fragment_op_arg (struct wined3d_string_buffer*,int,unsigned int,scalar_t__) ; 
 scalar_t__ tempreg ; 

__attribute__((used)) static void shader_glsl_ffp_fragment_op(struct wined3d_string_buffer *buffer, unsigned int stage, BOOL color,
        BOOL alpha, DWORD dst, DWORD op, DWORD dw_arg0, DWORD dw_arg1, DWORD dw_arg2)
{
    const char *dstmask, *dstreg, *arg0, *arg1, *arg2;

    if (color && alpha)
        dstmask = "";
    else if (color)
        dstmask = ".xyz";
    else
        dstmask = ".w";

    if (dst == tempreg)
        dstreg = "temp_reg";
    else
        dstreg = "ret";

    arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, dw_arg0);
    arg1 = shader_glsl_get_ffp_fragment_op_arg(buffer, 1, stage, dw_arg1);
    arg2 = shader_glsl_get_ffp_fragment_op_arg(buffer, 2, stage, dw_arg2);

    switch (op)
    {
        case WINED3D_TOP_DISABLE:
            break;

        case WINED3D_TOP_SELECT_ARG1:
            shader_addline(buffer, "%s%s = %s%s;\n", dstreg, dstmask, arg1, dstmask);
            break;

        case WINED3D_TOP_SELECT_ARG2:
            shader_addline(buffer, "%s%s = %s%s;\n", dstreg, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_MODULATE:
            shader_addline(buffer, "%s%s = %s%s * %s%s;\n", dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_MODULATE_4X:
            shader_addline(buffer, "%s%s = clamp(%s%s * %s%s * 4.0, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_MODULATE_2X:
            shader_addline(buffer, "%s%s = clamp(%s%s * %s%s * 2.0, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_ADD:
            shader_addline(buffer, "%s%s = clamp(%s%s + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_ADD_SIGNED:
            shader_addline(buffer, "%s%s = clamp(%s%s + (%s - vec4(0.5))%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_ADD_SIGNED_2X:
            shader_addline(buffer, "%s%s = clamp((%s%s + (%s - vec4(0.5))%s) * 2.0, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_SUBTRACT:
            shader_addline(buffer, "%s%s = clamp(%s%s - %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask);
            break;

        case WINED3D_TOP_ADD_SMOOTH:
            shader_addline(buffer, "%s%s = clamp((vec4(1.0) - %s)%s * %s%s + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask, arg1, dstmask);
            break;

        case WINED3D_TOP_BLEND_DIFFUSE_ALPHA:
            arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, WINED3DTA_DIFFUSE);
            shader_addline(buffer, "%s%s = mix(%s%s, %s%s, %s.w);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, dstmask, arg0);
            break;

        case WINED3D_TOP_BLEND_TEXTURE_ALPHA:
            arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, WINED3DTA_TEXTURE);
            shader_addline(buffer, "%s%s = mix(%s%s, %s%s, %s.w);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, dstmask, arg0);
            break;

        case WINED3D_TOP_BLEND_FACTOR_ALPHA:
            arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, WINED3DTA_TFACTOR);
            shader_addline(buffer, "%s%s = mix(%s%s, %s%s, %s.w);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, dstmask, arg0);
            break;

        case WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM:
            arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, WINED3DTA_TEXTURE);
            shader_addline(buffer, "%s%s = clamp(%s%s * (1.0 - %s.w) + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg2, dstmask, arg0, arg1, dstmask);
            break;

        case WINED3D_TOP_BLEND_CURRENT_ALPHA:
            arg0 = shader_glsl_get_ffp_fragment_op_arg(buffer, 0, stage, WINED3DTA_CURRENT);
            shader_addline(buffer, "%s%s = mix(%s%s, %s%s, %s.w);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, dstmask, arg0);
            break;

        case WINED3D_TOP_MODULATE_ALPHA_ADD_COLOR:
            shader_addline(buffer, "%s%s = clamp(%s%s * %s.w + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, arg1, dstmask);
            break;

        case WINED3D_TOP_MODULATE_COLOR_ADD_ALPHA:
            shader_addline(buffer, "%s%s = clamp(%s%s * %s%s + %s.w, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask, arg1);
            break;

        case WINED3D_TOP_MODULATE_INVALPHA_ADD_COLOR:
            shader_addline(buffer, "%s%s = clamp(%s%s * (1.0 - %s.w) + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, arg1, dstmask);
            break;
        case WINED3D_TOP_MODULATE_INVCOLOR_ADD_ALPHA:
            shader_addline(buffer, "%s%s = clamp((vec4(1.0) - %s)%s * %s%s + %s.w, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask, arg1);
            break;

        case WINED3D_TOP_BUMPENVMAP:
        case WINED3D_TOP_BUMPENVMAP_LUMINANCE:
            /* These are handled in the first pass, nothing to do. */
            break;

        case WINED3D_TOP_DOTPRODUCT3:
            shader_addline(buffer, "%s%s = vec4(clamp(dot(%s.xyz - 0.5, %s.xyz - 0.5) * 4.0, 0.0, 1.0))%s;\n",
                    dstreg, dstmask, arg1, arg2, dstmask);
            break;

        case WINED3D_TOP_MULTIPLY_ADD:
            shader_addline(buffer, "%s%s = clamp(%s%s * %s%s + %s%s, 0.0, 1.0);\n",
                    dstreg, dstmask, arg1, dstmask, arg2, dstmask, arg0, dstmask);
            break;

        case WINED3D_TOP_LERP:
            /* MSDN isn't quite right here. */
            shader_addline(buffer, "%s%s = mix(%s%s, %s%s, %s%s);\n",
                    dstreg, dstmask, arg2, dstmask, arg1, dstmask, arg0, dstmask);
            break;

        default:
            FIXME("Unhandled operation %#x.\n", op);
            break;
    }
}