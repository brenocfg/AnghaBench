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
struct wined3d_texture {int dummy; } ;
struct wined3d_context {size_t active_texture; scalar_t__* rev_tex_unit_map; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  STATE_COMPUTE_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  STATE_GRAPHICS_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  STATE_SAMPLER (scalar_t__) ; 
 scalar_t__ WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  context_invalidate_compute_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_bind (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

void wined3d_texture_bind_and_dirtify(struct wined3d_texture *texture,
        struct wined3d_context *context, BOOL srgb)
{
    /* We don't need a specific texture unit, but after binding the texture
     * the current unit is dirty. Read the unit back instead of switching to
     * 0, this avoids messing around with the state manager's GL states. The
     * current texture unit should always be a valid one.
     *
     * To be more specific, this is tricky because we can implicitly be
     * called from sampler() in state.c. This means we can't touch anything
     * other than whatever happens to be the currently active texture, or we
     * would risk marking already applied sampler states dirty again. */
    if (context->active_texture < ARRAY_SIZE(context->rev_tex_unit_map))
    {
        DWORD active_sampler = context->rev_tex_unit_map[context->active_texture];
        if (active_sampler != WINED3D_UNMAPPED_STAGE)
            context_invalidate_state(context, STATE_SAMPLER(active_sampler));
    }
    /* FIXME: Ideally we'd only do this when touching a binding that's used by
     * a shader. */
    context_invalidate_compute_state(context, STATE_COMPUTE_SHADER_RESOURCE_BINDING);
    context_invalidate_state(context, STATE_GRAPHICS_SHADER_RESOURCE_BINDING);

    wined3d_texture_bind(texture, context, srgb);
}