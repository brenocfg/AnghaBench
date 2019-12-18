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
struct wined3d_resource {int access; int usage; struct wined3d_format* format; } ;
struct TYPE_3__ {int /*<<< orphan*/  glBlitFramebuffer; } ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
struct wined3d_format {int* flags; int /*<<< orphan*/  color_fixup; int /*<<< orphan*/  id; } ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
struct TYPE_4__ {scalar_t__ offscreen_rendering_mode; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_FBO_ATTACHABLE ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3DUSAGE_RENDERTARGET ; 
#define  WINED3D_BLIT_OP_COLOR_BLIT 129 
#define  WINED3D_BLIT_OP_DEPTH_BLIT 128 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 int /*<<< orphan*/  is_complex_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_identity_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_scaling_fixup (int /*<<< orphan*/ ) ; 
 TYPE_2__ wined3d_settings ; 

__attribute__((used)) static BOOL fbo_blitter_supported(enum wined3d_blit_op blit_op, const struct wined3d_gl_info *gl_info,
        const struct wined3d_resource *src_resource, DWORD src_location,
        const struct wined3d_resource *dst_resource, DWORD dst_location)
{
    const struct wined3d_format *src_format = src_resource->format;
    const struct wined3d_format *dst_format = dst_resource->format;

    if ((wined3d_settings.offscreen_rendering_mode != ORM_FBO) || !gl_info->fbo_ops.glBlitFramebuffer)
        return FALSE;

    /* Source and/or destination need to be on the GL side */
    if (!(src_resource->access & dst_resource->access & WINED3D_RESOURCE_ACCESS_GPU))
        return FALSE;

    switch (blit_op)
    {
        case WINED3D_BLIT_OP_COLOR_BLIT:
            if (!((src_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_FBO_ATTACHABLE)
                    || (src_resource->usage & WINED3DUSAGE_RENDERTARGET)))
                return FALSE;
            if (!((dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_FBO_ATTACHABLE)
                    || (dst_resource->usage & WINED3DUSAGE_RENDERTARGET)))
                return FALSE;
            if ((src_format->id != dst_format->id || dst_location == WINED3D_LOCATION_DRAWABLE)
                    && (!is_identity_fixup(src_format->color_fixup) || !is_identity_fixup(dst_format->color_fixup)))
                return FALSE;
            break;

        case WINED3D_BLIT_OP_DEPTH_BLIT:
            if (!(src_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL)))
                return FALSE;
            if (!(dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL)))
                return FALSE;
            /* Accept pure swizzle fixups for depth formats. In general we
             * ignore the stencil component (if present) at the moment and the
             * swizzle is not relevant with just the depth component. */
            if (is_complex_fixup(src_format->color_fixup) || is_complex_fixup(dst_format->color_fixup)
                    || is_scaling_fixup(src_format->color_fixup) || is_scaling_fixup(dst_format->color_fixup))
                return FALSE;
            break;

        default:
            return FALSE;
    }

    return TRUE;
}