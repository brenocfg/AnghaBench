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
struct wined3d_rendertarget_info {int dummy; } ;
struct wined3d_fbo_entry_key {int /*<<< orphan*/ * objects; scalar_t__ rb_namespace; } ;
struct wined3d_context {TYPE_1__* gl_info; } ;
struct TYPE_4__ {unsigned int buffers; } ;
struct TYPE_3__ {TYPE_2__ limits; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_set_fbo_key_for_render_target (struct wined3d_context const*,struct wined3d_fbo_entry_key*,unsigned int,struct wined3d_rendertarget_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void context_generate_fbo_key(const struct wined3d_context *context,
        struct wined3d_fbo_entry_key *key, const struct wined3d_rendertarget_info *render_targets,
        const struct wined3d_rendertarget_info *depth_stencil, DWORD color_location, DWORD ds_location)
{
    unsigned int buffers = context->gl_info->limits.buffers;
    unsigned int i;

    key->rb_namespace = 0;
    context_set_fbo_key_for_render_target(context, key, 0, depth_stencil, ds_location);

    for (i = 0; i < buffers; ++i)
        context_set_fbo_key_for_render_target(context, key, i + 1, &render_targets[i], color_location);

    memset(&key->objects[buffers + 1], 0, (ARRAY_SIZE(key->objects) - buffers - 1) * sizeof(*key->objects));
}