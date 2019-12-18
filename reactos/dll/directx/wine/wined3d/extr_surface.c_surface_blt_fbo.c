#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* format; } ;
struct wined3d_texture {unsigned int level_count; TYPE_4__* swapchain; TYPE_2__ resource; } ;
struct wined3d_surface {struct wined3d_texture* container; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* p_glFlush ) () ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glColorMask ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glReadBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {TYPE_5__ gl; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* glBlitFramebuffer ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct wined3d_gl_info {TYPE_6__ gl_ops; TYPE_3__ fbo_ops; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int /*<<< orphan*/  win_handle; struct wined3d_gl_info* gl_info; int /*<<< orphan*/  valid; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_21__ {scalar_t__ strict_draw_ordering; } ;
struct TYPE_20__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_17__ {struct wined3d_texture* front_buffer; } ;
struct TYPE_14__ {scalar_t__ id; } ;
typedef  TYPE_7__ RECT ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int MAX_RENDER_TARGETS ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_surface*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_RB_RESOLVED ; 
 int /*<<< orphan*/  WINED3D_RS_COLORWRITE (int) ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
#define  WINED3D_TEXF_LINEAR 130 
#define  WINED3D_TEXF_NONE 129 
#define  WINED3D_TEXF_POINT 128 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device const*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,struct wined3d_surface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 struct wined3d_surface* context_get_rt_surface (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_surface*) ; 
 int /*<<< orphan*/  context_set_draw_buffer (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dtexturefiltertype (int) ; 
 scalar_t__ is_multisample_location (struct wined3d_texture*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 () ; 
 unsigned int surface_get_sub_resource_idx (struct wined3d_surface*) ; 
 int /*<<< orphan*/  surface_translate_drawable_coords (struct wined3d_surface*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  texture2d_is_full_rect (struct wined3d_texture*,unsigned int,TYPE_7__*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_7__ const*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int /*<<< orphan*/ ) ; 
 TYPE_8__ wined3d_settings ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void surface_blt_fbo(const struct wined3d_device *device,
        struct wined3d_context *old_ctx, enum wined3d_texture_filter_type filter,
        struct wined3d_surface *src_surface, DWORD src_location, const RECT *src_rect_in,
        struct wined3d_surface *dst_surface, DWORD dst_location, const RECT *dst_rect_in)
{
    unsigned int dst_sub_resource_idx = surface_get_sub_resource_idx(dst_surface);
    unsigned int src_sub_resource_idx = surface_get_sub_resource_idx(src_surface);
    struct wined3d_texture *dst_texture = dst_surface->container;
    struct wined3d_texture *src_texture = src_surface->container;
    const struct wined3d_gl_info *gl_info;
    struct wined3d_context *context = old_ctx;
    struct wined3d_surface *required_rt, *restore_rt = NULL;
    RECT src_rect, dst_rect;
    GLenum gl_filter;
    GLenum buffer;
    int i;

    TRACE("device %p, filter %s,\n", device, debug_d3dtexturefiltertype(filter));
    TRACE("src_surface %p, src_location %s, src_rect %s,\n",
            src_surface, wined3d_debug_location(src_location), wine_dbgstr_rect(src_rect_in));
    TRACE("dst_surface %p, dst_location %s, dst_rect %s.\n",
            dst_surface, wined3d_debug_location(dst_location), wine_dbgstr_rect(dst_rect_in));

    src_rect = *src_rect_in;
    dst_rect = *dst_rect_in;

    switch (filter)
    {
        case WINED3D_TEXF_LINEAR:
            gl_filter = GL_LINEAR;
            break;

        default:
            FIXME("Unsupported filter mode %s (%#x).\n", debug_d3dtexturefiltertype(filter), filter);
        case WINED3D_TEXF_NONE:
        case WINED3D_TEXF_POINT:
            gl_filter = GL_NEAREST;
            break;
    }

    /* Resolve the source surface first if needed. */
    if (is_multisample_location(src_texture, src_location)
            && (src_texture->resource.format->id != dst_texture->resource.format->id
                || abs(src_rect.bottom - src_rect.top) != abs(dst_rect.bottom - dst_rect.top)
                || abs(src_rect.right - src_rect.left) != abs(dst_rect.right - dst_rect.left)))
        src_location = WINED3D_LOCATION_RB_RESOLVED;

    /* Make sure the locations are up-to-date. Loading the destination
     * surface isn't required if the entire surface is overwritten. (And is
     * in fact harmful if we're being called by surface_load_location() with
     * the purpose of loading the destination surface.) */
    wined3d_texture_load_location(src_texture, src_sub_resource_idx, old_ctx, src_location);
    if (!texture2d_is_full_rect(dst_texture, dst_sub_resource_idx % dst_texture->level_count, &dst_rect))
        wined3d_texture_load_location(dst_texture, dst_sub_resource_idx, old_ctx, dst_location);
    else
        wined3d_texture_prepare_location(dst_texture, dst_sub_resource_idx, old_ctx, dst_location);


    if (src_location == WINED3D_LOCATION_DRAWABLE) required_rt = src_surface;
    else if (dst_location == WINED3D_LOCATION_DRAWABLE) required_rt = dst_surface;
    else required_rt = NULL;

    restore_rt = context_get_rt_surface(old_ctx);
    if (restore_rt != required_rt)
        context = context_acquire(device, required_rt ? required_rt->container : NULL,
                required_rt ? surface_get_sub_resource_idx(required_rt) : 0);
    else
        restore_rt = NULL;

    if (!context->valid)
    {
        context_release(context);
        WARN("Invalid context, skipping blit.\n");
        return;
    }

    gl_info = context->gl_info;

    if (src_location == WINED3D_LOCATION_DRAWABLE)
    {
        TRACE("Source surface %p is onscreen.\n", src_surface);
        buffer = wined3d_texture_get_gl_buffer(src_texture);
        surface_translate_drawable_coords(src_surface, context->win_handle, &src_rect);
    }
    else
    {
        TRACE("Source surface %p is offscreen.\n", src_surface);
        buffer = GL_COLOR_ATTACHMENT0;
    }

    context_apply_fbo_state_blit(context, GL_READ_FRAMEBUFFER, src_surface, NULL, src_location);
    gl_info->gl_ops.gl.p_glReadBuffer(buffer);
    checkGLcall("glReadBuffer()");
    context_check_fbo_status(context, GL_READ_FRAMEBUFFER);

    if (dst_location == WINED3D_LOCATION_DRAWABLE)
    {
        TRACE("Destination surface %p is onscreen.\n", dst_surface);
        buffer = wined3d_texture_get_gl_buffer(dst_texture);
        surface_translate_drawable_coords(dst_surface, context->win_handle, &dst_rect);
    }
    else
    {
        TRACE("Destination surface %p is offscreen.\n", dst_surface);
        buffer = GL_COLOR_ATTACHMENT0;
    }

    context_apply_fbo_state_blit(context, GL_DRAW_FRAMEBUFFER, dst_surface, NULL, dst_location);
    context_set_draw_buffer(context, buffer);
    context_check_fbo_status(context, GL_DRAW_FRAMEBUFFER);
    context_invalidate_state(context, STATE_FRAMEBUFFER);

    gl_info->gl_ops.gl.p_glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    for (i = 0; i < MAX_RENDER_TARGETS; ++i)
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_COLORWRITE(i)));

    gl_info->gl_ops.gl.p_glDisable(GL_SCISSOR_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));

    gl_info->fbo_ops.glBlitFramebuffer(src_rect.left, src_rect.top, src_rect.right, src_rect.bottom,
            dst_rect.left, dst_rect.top, dst_rect.right, dst_rect.bottom, GL_COLOR_BUFFER_BIT, gl_filter);
    checkGLcall("glBlitFramebuffer()");

    if (wined3d_settings.strict_draw_ordering || (dst_location == WINED3D_LOCATION_DRAWABLE
            && dst_texture->swapchain->front_buffer == dst_texture))
        gl_info->gl_ops.gl.p_glFlush();

    if (restore_rt)
        context_restore(context, restore_rt);
}