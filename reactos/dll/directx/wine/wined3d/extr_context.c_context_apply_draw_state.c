#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int /*<<< orphan*/ * unordered_access_view; int /*<<< orphan*/ * shader; scalar_t__ index_buffer; TYPE_1__* streams; struct wined3d_fb_state* fb; } ;
struct TYPE_11__ {scalar_t__ combined_samplers; scalar_t__ graphics_samplers; int /*<<< orphan*/  buffers; } ;
struct wined3d_gl_info {TYPE_5__ limits; int /*<<< orphan*/ * supported; } ;
struct wined3d_fb_state {int /*<<< orphan*/  depth_stencil; int /*<<< orphan*/  render_targets; } ;
struct wined3d_device {int /*<<< orphan*/  shader_priv; TYPE_4__* shader_backend; } ;
struct TYPE_9__ {int use_map; scalar_t__ all_vbo; TYPE_2__* elements; } ;
struct wined3d_context {unsigned int numDirtyEntries; int* dirtyArray; unsigned int* isStateDirty; unsigned int shader_update_mask; int update_compute_shader_resource_bindings; int update_compute_unordered_access_view_bindings; int /*<<< orphan*/  last_was_blit; scalar_t__ update_unordered_access_view_bindings; scalar_t__ update_shader_resource_bindings; scalar_t__ constant_update_mask; TYPE_3__ stream_info; struct wined3d_gl_info* gl_info; struct StateEntry* state_table; } ;
struct StateEntry {int /*<<< orphan*/  (* apply ) (struct wined3d_context*,struct wined3d_state const*,int) ;} ;
typedef  int WORD ;
struct TYPE_12__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* shader_load_constants ) (int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_state const*) ;int /*<<< orphan*/  (* shader_select ) (int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_state const*) ;} ;
struct TYPE_8__ {size_t stream_idx; } ;
struct TYPE_7__ {scalar_t__ buffer; } ;
typedef  int DWORD ;
typedef  unsigned int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARB_FRAMEBUFFER_NO_ATTACHMENTS ; 
 int CHAR_BIT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_SHADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_STREAMSRC ; 
 int /*<<< orphan*/  STATE_VDECL ; 
 int /*<<< orphan*/  TRUE ; 
 size_t WINED3D_PIPELINE_GRAPHICS ; 
 unsigned int WINED3D_SHADER_TYPE_COMPUTE ; 
 unsigned int WINED3D_SHADER_TYPE_GRAPHICS_COUNT ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  context_bind_shader_resources (struct wined3d_context*,struct wined3d_state const*,unsigned int) ; 
 int /*<<< orphan*/  context_bind_unordered_access_views (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_load_shader_resources (struct wined3d_context*,struct wined3d_state const*,unsigned int) ; 
 int /*<<< orphan*/  context_load_stream_output_buffers (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_load_unordered_access_resources (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_preload_textures (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_set_render_offscreen (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_update_stream_info (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_update_tex_unit_map (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_validate_onscreen_formats (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_framebuffer_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_context*,struct wined3d_state const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_buffer_load (scalar_t__,struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_buffer_load_sysmem (scalar_t__,struct wined3d_context*) ; 
 TYPE_6__ wined3d_settings ; 

__attribute__((used)) static BOOL context_apply_draw_state(struct wined3d_context *context,
        const struct wined3d_device *device, const struct wined3d_state *state)
{
    const struct StateEntry *state_table = context->state_table;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_fb_state *fb = state->fb;
    unsigned int i;
    WORD map;

    if (!have_framebuffer_attachment(gl_info->limits.buffers, fb->render_targets, fb->depth_stencil))
    {
        if (!gl_info->supported[ARB_FRAMEBUFFER_NO_ATTACHMENTS])
        {
            FIXME("OpenGL implementation does not support framebuffers with no attachments.\n");
            return FALSE;
        }

        context_set_render_offscreen(context, TRUE);
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO && isStateDirty(context, STATE_FRAMEBUFFER))
    {
        context_validate_onscreen_formats(context, fb->depth_stencil);
    }

    /* Preload resources before FBO setup. Texture preload in particular may
     * result in changes to the current FBO, due to using e.g. FBO blits for
     * updating a resource location. */
    context_update_tex_unit_map(context, state);
    context_preload_textures(context, state);
    context_load_shader_resources(context, state, ~(1u << WINED3D_SHADER_TYPE_COMPUTE));
    context_load_unordered_access_resources(context, state->shader[WINED3D_SHADER_TYPE_PIXEL],
            state->unordered_access_view[WINED3D_PIPELINE_GRAPHICS]);
    context_load_stream_output_buffers(context, state);
    /* TODO: Right now the dependency on the vertex shader is necessary
     * since wined3d_stream_info_from_declaration() depends on the reg_maps of
     * the current VS but maybe it's possible to relax the coupling in some
     * situations at least. */
    if (isStateDirty(context, STATE_VDECL) || isStateDirty(context, STATE_STREAMSRC)
            || isStateDirty(context, STATE_SHADER(WINED3D_SHADER_TYPE_VERTEX)))
    {
        context_update_stream_info(context, state);
    }
    else
    {
        for (i = 0, map = context->stream_info.use_map; map; map >>= 1, ++i)
        {
            if (map & 1)
                wined3d_buffer_load(state->streams[context->stream_info.elements[i].stream_idx].buffer,
                        context, state);
        }
        /* Loading the buffers above may have invalidated the stream info. */
        if (isStateDirty(context, STATE_STREAMSRC))
            context_update_stream_info(context, state);
    }
    if (state->index_buffer)
    {
        if (context->stream_info.all_vbo)
            wined3d_buffer_load(state->index_buffer, context, state);
        else
            wined3d_buffer_load_sysmem(state->index_buffer, context);
    }

    for (i = 0; i < context->numDirtyEntries; ++i)
    {
        DWORD rep = context->dirtyArray[i];
        DWORD idx = rep / (sizeof(*context->isStateDirty) * CHAR_BIT);
        BYTE shift = rep & ((sizeof(*context->isStateDirty) * CHAR_BIT) - 1);
        context->isStateDirty[idx] &= ~(1u << shift);
        state_table[rep].apply(context, state, rep);
    }

    if (context->shader_update_mask & ~(1u << WINED3D_SHADER_TYPE_COMPUTE))
    {
        device->shader_backend->shader_select(device->shader_priv, context, state);
        context->shader_update_mask &= 1u << WINED3D_SHADER_TYPE_COMPUTE;
    }

    if (context->constant_update_mask)
    {
        device->shader_backend->shader_load_constants(device->shader_priv, context, state);
        context->constant_update_mask = 0;
    }

    if (context->update_shader_resource_bindings)
    {
        for (i = 0; i < WINED3D_SHADER_TYPE_GRAPHICS_COUNT; ++i)
            context_bind_shader_resources(context, state, i);
        context->update_shader_resource_bindings = 0;
        if (gl_info->limits.combined_samplers == gl_info->limits.graphics_samplers)
            context->update_compute_shader_resource_bindings = 1;
    }

    if (context->update_unordered_access_view_bindings)
    {
        context_bind_unordered_access_views(context,
                state->shader[WINED3D_SHADER_TYPE_PIXEL],
                state->unordered_access_view[WINED3D_PIPELINE_GRAPHICS]);
        context->update_unordered_access_view_bindings = 0;
        context->update_compute_unordered_access_view_bindings = 1;
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        context_check_fbo_status(context, GL_FRAMEBUFFER);
    }

    context->numDirtyEntries = 0; /* This makes the whole list clean */
    context->last_was_blit = FALSE;

    return TRUE;
}