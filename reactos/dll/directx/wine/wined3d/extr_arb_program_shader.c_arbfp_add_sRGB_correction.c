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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,char const*,...) ; 

__attribute__((used)) static void arbfp_add_sRGB_correction(struct wined3d_string_buffer *buffer, const char *fragcolor,
        const char *tmp1, const char *tmp2, const char *tmp3, const char *tmp4, BOOL condcode)
{
    /* Perform sRGB write correction. See GLX_EXT_framebuffer_sRGB */

    if(condcode)
    {
        /* Sigh. MOVC CC doesn't work, so use one of the temps as dummy dest */
        shader_addline(buffer, "SUBC %s, %s.x, srgb_consts1.x;\n", tmp1, fragcolor);
        /* Calculate the > 0.0031308 case */
        shader_addline(buffer, "POW %s.x (GE), %s.x, srgb_consts0.x;\n", fragcolor, fragcolor);
        shader_addline(buffer, "POW %s.y (GE), %s.y, srgb_consts0.x;\n", fragcolor, fragcolor);
        shader_addline(buffer, "POW %s.z (GE), %s.z, srgb_consts0.x;\n", fragcolor, fragcolor);
        shader_addline(buffer, "MUL %s.xyz (GE), %s, srgb_consts0.y;\n", fragcolor, fragcolor);
        shader_addline(buffer, "SUB %s.xyz (GE), %s, srgb_consts0.z;\n", fragcolor, fragcolor);
        /* Calculate the < case */
        shader_addline(buffer, "MUL %s.xyz (LT), srgb_consts0.w, %s;\n", fragcolor, fragcolor);
    }
    else
    {
        /* Calculate the > 0.0031308 case */
        shader_addline(buffer, "POW %s.x, %s.x, srgb_consts0.x;\n", tmp1, fragcolor);
        shader_addline(buffer, "POW %s.y, %s.y, srgb_consts0.x;\n", tmp1, fragcolor);
        shader_addline(buffer, "POW %s.z, %s.z, srgb_consts0.x;\n", tmp1, fragcolor);
        shader_addline(buffer, "MUL %s, %s, srgb_consts0.y;\n", tmp1, tmp1);
        shader_addline(buffer, "SUB %s, %s, srgb_consts0.z;\n", tmp1, tmp1);
        /* Calculate the < case */
        shader_addline(buffer, "MUL %s, srgb_consts0.w, %s;\n", tmp2, fragcolor);
        /* Get 1.0 / 0.0 masks for > 0.0031308 and < 0.0031308 */
        shader_addline(buffer, "SLT %s, srgb_consts1.x, %s;\n", tmp3, fragcolor);
        shader_addline(buffer, "SGE %s, srgb_consts1.x, %s;\n", tmp4, fragcolor);
        /* Store the components > 0.0031308 in the destination */
        shader_addline(buffer, "MUL %s.xyz, %s, %s;\n", fragcolor, tmp1, tmp3);
        /* Add the components that are < 0.0031308 */
        shader_addline(buffer, "MAD %s.xyz, %s, %s, %s;\n", fragcolor, tmp2, tmp4, fragcolor);
        /* Move everything into result.color at once. Nvidia hardware cannot handle partial
        * result.color writes(.rgb first, then .a), or handle overwriting already written
        * components. The assembler uses a temporary register in this case, which is usually
        * not allocated from one of our registers that were used earlier.
        */
    }
    /* [0.0;1.0] clamping. Not needed, this is done implicitly */
}