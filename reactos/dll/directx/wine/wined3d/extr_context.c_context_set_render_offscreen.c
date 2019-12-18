#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_context {scalar_t__ render_offscreen; TYPE_1__* gl_info; } ;
struct TYPE_2__ {scalar_t__* supported; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 size_t ARB_FRAGMENT_COORD_CONVENTIONS ; 
 int /*<<< orphan*/  STATE_FRONTFACE ; 
 int /*<<< orphan*/  STATE_POINTSPRITECOORDORIGIN ; 
 int /*<<< orphan*/  STATE_SCISSORRECT ; 
 int /*<<< orphan*/  STATE_SHADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_TRANSFORM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_VIEWPORT ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_DOMAIN ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  WINED3D_TS_PROJECTION ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_set_render_offscreen(struct wined3d_context *context, BOOL offscreen)
{
    if (context->render_offscreen == offscreen)
        return;

    context_invalidate_state(context, STATE_VIEWPORT);
    context_invalidate_state(context, STATE_SCISSORRECT);
    if (!context->gl_info->supported[ARB_CLIP_CONTROL])
    {
        context_invalidate_state(context, STATE_FRONTFACE);
        context_invalidate_state(context, STATE_POINTSPRITECOORDORIGIN);
        context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_PROJECTION));
    }
    context_invalidate_state(context, STATE_SHADER(WINED3D_SHADER_TYPE_DOMAIN));
    if (context->gl_info->supported[ARB_FRAGMENT_COORD_CONVENTIONS])
        context_invalidate_state(context, STATE_SHADER(WINED3D_SHADER_TYPE_PIXEL));
    context->render_offscreen = offscreen;
}