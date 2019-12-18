#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int samples; int /*<<< orphan*/ * samplers; } ;
struct wined3d_gl_info {int quirks; TYPE_1__ limits; scalar_t__* supported; } ;
struct wined3d_format_texture_info {int flags; } ;
struct wined3d_format {scalar_t__ glInternal; scalar_t__ glGammaInternal; int* flags; scalar_t__ id; unsigned int multisample_types; } ;
struct wined3d_adapter {int dummy; } ;
struct TYPE_4__ {scalar_t__ offscreen_rendering_mode; } ;
typedef  unsigned int GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_DEPTH_TEXTURE ; 
 size_t ARB_INTERNALFORMAT_QUERY ; 
 size_t ARB_INTERNALFORMAT_QUERY2 ; 
 size_t ARB_TEXTURE_MULTISAMPLE ; 
 int CHAR_BIT ; 
 size_t EXT_TEXTURE_SRGB ; 
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FILTER ; 
 int /*<<< orphan*/  GL_NUM_SAMPLE_COUNTS ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_SAMPLES ; 
 int /*<<< orphan*/  GL_SRGB_READ ; 
 int /*<<< orphan*/  GL_SRGB_WRITE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_MULTISAMPLE ; 
 int /*<<< orphan*/  GL_VERTEX_TEXTURE ; 
 int MAX_MULTISAMPLE_TYPES ; 
 scalar_t__ ORM_FBO ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_FILTERING ; 
 int WINED3DFMT_FLAG_RENDERTARGET ; 
 int WINED3DFMT_FLAG_SRGB_READ ; 
 int WINED3DFMT_FLAG_SRGB_WRITE ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3DFMT_FLAG_TEXTURE ; 
 int WINED3DFMT_FLAG_VTF ; 
 scalar_t__ WINED3DFMT_R32G32B32A32_FLOAT ; 
 scalar_t__ WINED3DFMT_R32_FLOAT ; 
 size_t WINED3D_GL_RES_TYPE_RB ; 
 size_t WINED3D_GL_RES_TYPE_TEX_1D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_3D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_CUBE ; 
 size_t WINED3D_GL_RES_TYPE_TEX_RECT ; 
 int WINED3D_QUIRK_LIMITED_TEX_FILTERING ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  format_clear_flag (struct wined3d_format*,int) ; 
 int /*<<< orphan*/  format_set_flag (struct wined3d_format*,int) ; 
 int /*<<< orphan*/  glGetInternalformativ (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  query_format_flag (struct wined3d_gl_info*,struct wined3d_format*,scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  query_view_class (struct wined3d_format*) ; 
 unsigned int wined3d_log2i (unsigned int) ; 
 TYPE_2__ wined3d_settings ; 

__attribute__((used)) static void query_internal_format(struct wined3d_adapter *adapter,
        struct wined3d_format *format, const struct wined3d_format_texture_info *texture_info,
        struct wined3d_gl_info *gl_info, BOOL srgb_write_supported, BOOL srgb_format)
{
    GLint count, multisample_types[MAX_MULTISAMPLE_TYPES];
    unsigned int i, max_log2;
    GLenum target;

    if (gl_info->supported[ARB_INTERNALFORMAT_QUERY2])
    {
        query_format_flag(gl_info, format, format->glInternal, GL_VERTEX_TEXTURE,
                WINED3DFMT_FLAG_VTF, "vertex texture usage");
        query_format_flag(gl_info, format, format->glInternal, GL_FILTER,
                WINED3DFMT_FLAG_FILTERING, "filtering");

        if (srgb_format || format->glGammaInternal != format->glInternal)
        {
            query_format_flag(gl_info, format, format->glGammaInternal, GL_SRGB_READ,
                    WINED3DFMT_FLAG_SRGB_READ, "sRGB read");

            if (srgb_write_supported)
                query_format_flag(gl_info, format, format->glGammaInternal, GL_SRGB_WRITE,
                        WINED3DFMT_FLAG_SRGB_WRITE, "sRGB write");
            else
                format_clear_flag(format, WINED3DFMT_FLAG_SRGB_WRITE);

            if (!(format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & (WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE)))
                format->glGammaInternal = format->glInternal;
            else if (wined3d_settings.offscreen_rendering_mode != ORM_FBO
                    && gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
                format->glInternal = format->glGammaInternal;
        }
    }
    else
    {
        if (!gl_info->limits.samplers[WINED3D_SHADER_TYPE_VERTEX])
            format_clear_flag(format, WINED3DFMT_FLAG_VTF);

        if (!(gl_info->quirks & WINED3D_QUIRK_LIMITED_TEX_FILTERING))
            format_set_flag(format, WINED3DFMT_FLAG_FILTERING);
        else if (format->id != WINED3DFMT_R32G32B32A32_FLOAT && format->id != WINED3DFMT_R32_FLOAT)
            format_clear_flag(format, WINED3DFMT_FLAG_VTF);

        if (srgb_format || format->glGammaInternal != format->glInternal)
        {
            /* Filter sRGB capabilities if EXT_texture_sRGB is not supported. */
            if (!gl_info->supported[EXT_TEXTURE_SRGB])
            {
                format->glGammaInternal = format->glInternal;
                format_clear_flag(format, WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE);
            }
            else if (wined3d_settings.offscreen_rendering_mode != ORM_FBO
                    && gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
            {
                format->glInternal = format->glGammaInternal;
            }
        }

        if ((format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_SRGB_WRITE) && !srgb_write_supported)
            format_clear_flag(format, WINED3DFMT_FLAG_SRGB_WRITE);

        if (!gl_info->supported[ARB_DEPTH_TEXTURE]
                && texture_info->flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
        {
            format->flags[WINED3D_GL_RES_TYPE_TEX_1D] &= ~WINED3DFMT_FLAG_TEXTURE;
            format->flags[WINED3D_GL_RES_TYPE_TEX_2D] &= ~WINED3DFMT_FLAG_TEXTURE;
            format->flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
            format->flags[WINED3D_GL_RES_TYPE_TEX_CUBE] &= ~WINED3DFMT_FLAG_TEXTURE;
            format->flags[WINED3D_GL_RES_TYPE_TEX_RECT] &= ~WINED3DFMT_FLAG_TEXTURE;
        }
    }

    query_view_class(format);

    if (format->glInternal && format->flags[WINED3D_GL_RES_TYPE_RB]
            & (WINED3DFMT_FLAG_RENDERTARGET | WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
    {
        if (gl_info->supported[ARB_INTERNALFORMAT_QUERY])
        {
            target = gl_info->supported[ARB_TEXTURE_MULTISAMPLE] ? GL_TEXTURE_2D_MULTISAMPLE : GL_RENDERBUFFER;
            count = 0;
            GL_EXTCALL(glGetInternalformativ(target, format->glInternal,
                    GL_NUM_SAMPLE_COUNTS, 1, &count));
            count = min(count, MAX_MULTISAMPLE_TYPES);
            GL_EXTCALL(glGetInternalformativ(target, format->glInternal,
                    GL_SAMPLES, count, multisample_types));
            checkGLcall("query sample counts");
            for (i = 0; i < count; ++i)
            {
                if (multisample_types[i] > sizeof(format->multisample_types) * CHAR_BIT)
                    continue;
                format->multisample_types |= 1u << (multisample_types[i] - 1);
            }
        }
        else
        {
#ifdef __REACTOS__
            if (gl_info->limits.samples) {
#endif
                max_log2 = wined3d_log2i(min(gl_info->limits.samples,
                        sizeof(format->multisample_types) * CHAR_BIT));
                for (i = 1; i <= max_log2; ++i)
                    format->multisample_types |= 1u << ((1u << i) - 1);
#ifdef __REACTOS__
            }
#endif
        }
    }
}