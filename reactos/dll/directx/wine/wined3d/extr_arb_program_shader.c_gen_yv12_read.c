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
struct arbfp_blit_type {scalar_t__ res_type; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3D_GL_RES_TYPE_TEX_2D ; 
 char* arbfp_texture_target (scalar_t__) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_append_imm_vec4 (struct wined3d_string_buffer*,float const*) ; 

__attribute__((used)) static BOOL gen_yv12_read(struct wined3d_string_buffer *buffer, const struct arbfp_blit_type *type,
        char *luminance)
{
    const char *tex;
    static const float yv12_coef[]
            = {2.0f / 3.0f, 1.0f / 6.0f, (2.0f / 3.0f) + (1.0f / 6.0f), 1.0f / 3.0f};

    tex = arbfp_texture_target(type->res_type);

    /* YV12 surfaces contain a WxH sized luminance plane, followed by a (W/2)x(H/2)
     * V and a (W/2)x(H/2) U plane, each with 8 bit per pixel. So the effective
     * bitdepth is 12 bits per pixel. Since the U and V planes have only half the
     * pitch of the luminance plane, the packing into the gl texture is a bit
     * unfortunate. If the whole texture is interpreted as luminance data it looks
     * approximately like this:
     *
     *        +----------------------------------+----
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |   2
     *        |            LUMINANCE             |   -
     *        |                                  |   3
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        +----------------+-----------------+----
     *        |                |                 |
     *        |  V even rows   |  V odd rows     |
     *        |                |                 |   1
     *        +----------------+------------------   -
     *        |                |                 |   3
     *        |  U even rows   |  U odd rows     |
     *        |                |                 |
     *        +----------------+-----------------+----
     *        |                |                 |
     *        |     0.5        |       0.5       |
     *
     * So it appears as if there are 4 chroma images, but in fact the odd rows
     * in the chroma images are in the same row as the even ones. So it is
     * kinda tricky to read
     *
     * When reading from rectangle textures, keep in mind that the input y coordinates
     * go from 0 to d3d_height, whereas the opengl texture height is 1.5 * d3d_height
     */
    shader_addline(buffer, "PARAM yv12_coef = ");
    shader_arb_append_imm_vec4(buffer, yv12_coef);
    shader_addline(buffer, ";\n");

    shader_addline(buffer, "MOV texcrd, fragment.texcoord[0];\n");
    /* the chroma planes have only half the width */
    shader_addline(buffer, "MUL texcrd.x, texcrd.x, coef.y;\n");

    /* The first value is between 2/3 and 5/6th of the texture's height, so scale+bias
     * the coordinate. Also read the right side of the image when reading odd lines
     *
     * Don't forget to clamp the y values in into the range, otherwise we'll get filtering
     * bleeding
     */
    if (type->res_type == WINED3D_GL_RES_TYPE_TEX_2D)
    {

        shader_addline(buffer, "RCP chroma.w, size.y;\n");

        shader_addline(buffer, "MUL texcrd2.y, texcrd.y, size.y;\n");

        shader_addline(buffer, "FLR texcrd2.y, texcrd2.y;\n");
        shader_addline(buffer, "MAD texcrd.y, texcrd.y, yv12_coef.y, yv12_coef.x;\n");

        /* Read odd lines from the right side(add size * 0.5 to the x coordinate */
        shader_addline(buffer, "ADD texcrd2.x, texcrd2.y, yv12_coef.y;\n"); /* To avoid 0.5 == 0.5 comparisons */
        shader_addline(buffer, "FRC texcrd2.x, texcrd2.x;\n");
        shader_addline(buffer, "SGE texcrd2.x, texcrd2.x, coef.y;\n");
        shader_addline(buffer, "MAD texcrd.x, texcrd2.x, coef.y, texcrd.x;\n");

        /* clamp, keep the half pixel origin in mind */
        shader_addline(buffer, "MAD temp.y, coef.y, chroma.w, yv12_coef.x;\n");
        shader_addline(buffer, "MAX texcrd.y, temp.y, texcrd.y;\n");
        shader_addline(buffer, "MAD temp.y, -coef.y, chroma.w, yv12_coef.z;\n");
        shader_addline(buffer, "MIN texcrd.y, temp.y, texcrd.y;\n");
    }
    else
    {
        /* Read from [size - size+size/4] */
        shader_addline(buffer, "FLR texcrd.y, texcrd.y;\n");
        shader_addline(buffer, "MAD texcrd.y, texcrd.y, coef.w, size.y;\n");

        /* Read odd lines from the right side(add size * 0.5 to the x coordinate */
        shader_addline(buffer, "ADD texcrd2.x, texcrd.y, yv12_coef.y;\n"); /* To avoid 0.5 == 0.5 comparisons */
        shader_addline(buffer, "FRC texcrd2.x, texcrd2.x;\n");
        shader_addline(buffer, "SGE texcrd2.x, texcrd2.x, coef.y;\n");
        shader_addline(buffer, "MUL texcrd2.x, texcrd2.x, size.x;\n");
        shader_addline(buffer, "MAD texcrd.x, texcrd2.x, coef.y, texcrd.x;\n");

        /* Make sure to read exactly from the pixel center */
        shader_addline(buffer, "FLR texcrd.y, texcrd.y;\n");
        shader_addline(buffer, "ADD texcrd.y, texcrd.y, coef.y;\n");

        /* Clamp */
        shader_addline(buffer, "MAD temp.y, size.y, coef.w, size.y;\n");
        shader_addline(buffer, "ADD temp.y, temp.y, -coef.y;\n");
        shader_addline(buffer, "MIN texcrd.y, temp.y, texcrd.y;\n");
        shader_addline(buffer, "ADD temp.y, size.y, coef.y;\n");
        shader_addline(buffer, "MAX texcrd.y, temp.y, texcrd.y;\n");
    }
    /* Read the texture, put the result into the output register */
    shader_addline(buffer, "TEX temp, texcrd, texture[0], %s;\n", tex);
    shader_addline(buffer, "MOV chroma.x, temp.w;\n");

    /* The other chroma value is 1/6th of the texture lower, from 5/6th to 6/6th
     * No need to clamp because we're just reusing the already clamped value from above
     */
    if (type->res_type == WINED3D_GL_RES_TYPE_TEX_2D)
        shader_addline(buffer, "ADD texcrd.y, texcrd.y, yv12_coef.y;\n");
    else
        shader_addline(buffer, "MAD texcrd.y, size.y, coef.w, texcrd.y;\n");
    shader_addline(buffer, "TEX temp, texcrd, texture[0], %s;\n", tex);
    shader_addline(buffer, "MOV chroma.y, temp.w;\n");

    /* Sample the luminance value. It is in the top 2/3rd of the texture, so scale the y coordinate.
     * Clamp the y coordinate to prevent the chroma values from bleeding into the sampled luminance
     * values due to filtering
     */
    shader_addline(buffer, "MOV texcrd, fragment.texcoord[0];\n");
    if (type->res_type == WINED3D_GL_RES_TYPE_TEX_2D)
    {
        /* Multiply the y coordinate by 2/3 and clamp it */
        shader_addline(buffer, "MUL texcrd.y, texcrd.y, yv12_coef.x;\n");
        shader_addline(buffer, "MAD temp.y, -coef.y, chroma.w, yv12_coef.x;\n");
        shader_addline(buffer, "MIN texcrd.y, temp.y, texcrd.y;\n");
        shader_addline(buffer, "TEX luminance, texcrd, texture[0], %s;\n", tex);
    }
    else
    {
        /* Reading from texture_rectangles is pretty straightforward, just use the unmodified
         * texture coordinate. It is still a good idea to clamp it though, since the opengl texture
         * is bigger
         */
        shader_addline(buffer, "ADD temp.x, size.y, -coef.y;\n");
        shader_addline(buffer, "MIN texcrd.y, texcrd.y, size.x;\n");
        shader_addline(buffer, "TEX luminance, texcrd, texture[0], %s;\n", tex);
    }
    *luminance = 'a';

    return TRUE;
}