#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_resource {int access; int usage; struct wined3d_format* format; } ;
struct wined3d_format {int* flags; scalar_t__ id; int /*<<< orphan*/  color_fixup; } ;
struct wined3d_context {TYPE_2__* gl_info; TYPE_1__* d3d_info; } ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
struct TYPE_6__ {int /*<<< orphan*/  offscreen_rendering_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/ * supported; } ;
struct TYPE_4__ {int /*<<< orphan*/  shader_color_key; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  ORM_BACKBUFFER ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int WINED3DFMT_FLAG_COMPRESSED ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3DUSAGE_RENDERTARGET ; 
#define  WINED3D_BLIT_OP_COLOR_BLIT 130 
#define  WINED3D_BLIT_OP_COLOR_BLIT_ALPHATEST 129 
#define  WINED3D_BLIT_OP_COLOR_BLIT_CKEY 128 
 int WINED3D_BLIT_OP_DEPTH_BLIT ; 
 int WINED3D_BLIT_OP_RAW_BLIT ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 int /*<<< orphan*/  d3d ; 
 int /*<<< orphan*/  dump_color_fixup_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_identity_fixup (int /*<<< orphan*/ ) ; 
 TYPE_3__ wined3d_settings ; 

__attribute__((used)) static BOOL ffp_blit_supported(enum wined3d_blit_op blit_op, const struct wined3d_context *context,
        const struct wined3d_resource *src_resource, DWORD src_location,
        const struct wined3d_resource *dst_resource, DWORD dst_location)
{
    const struct wined3d_format *src_format = src_resource->format;
    const struct wined3d_format *dst_format = dst_resource->format;
    BOOL decompress;

    decompress = src_format && (src_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_COMPRESSED)
            && !(dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_COMPRESSED);
    if (!decompress && !(src_resource->access & dst_resource->access & WINED3D_RESOURCE_ACCESS_GPU))
    {
        TRACE("Source or destination resource is not GPU accessible.\n");
        return FALSE;
    }

    if (blit_op == WINED3D_BLIT_OP_RAW_BLIT && dst_format->id == src_format->id)
    {
        if (dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
            blit_op = WINED3D_BLIT_OP_DEPTH_BLIT;
        else
            blit_op = WINED3D_BLIT_OP_COLOR_BLIT;
    }

    switch (blit_op)
    {
        case WINED3D_BLIT_OP_COLOR_BLIT_CKEY:
            if (context->d3d_info->shader_color_key)
            {
                TRACE("Color keying requires converted textures.\n");
                return FALSE;
            }
        case WINED3D_BLIT_OP_COLOR_BLIT:
        case WINED3D_BLIT_OP_COLOR_BLIT_ALPHATEST:
            if (!context->gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
                return FALSE;

            if (TRACE_ON(d3d))
            {
                TRACE("Checking support for fixup:\n");
                dump_color_fixup_desc(src_format->color_fixup);
            }

            /* We only support identity conversions. */
            if (!is_identity_fixup(src_format->color_fixup)
                    || !is_identity_fixup(dst_format->color_fixup))
            {
                if (wined3d_settings.offscreen_rendering_mode == ORM_BACKBUFFER
                        && dst_format->id == src_format->id && dst_location == WINED3D_LOCATION_DRAWABLE)
                {
                    WARN("Claiming fixup support because of ORM_BACKBUFFER.\n");
                }
                else
                {
                    TRACE("Fixups are not supported.\n");
                    return FALSE;
                }
            }

            if (!(dst_resource->usage & WINED3DUSAGE_RENDERTARGET))
            {
                TRACE("Can only blit to render targets.\n");
                return FALSE;
            }
            return TRUE;

        default:
            TRACE("Unsupported blit operation %#x.\n", blit_op);
            return FALSE;
    }
}