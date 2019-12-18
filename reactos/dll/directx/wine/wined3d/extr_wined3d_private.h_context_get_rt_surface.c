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
struct wined3d_texture {TYPE_2__* sub_resources; } ;
struct wined3d_surface {int dummy; } ;
struct TYPE_6__ {size_t sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {TYPE_3__ current_rt; } ;
struct TYPE_4__ {struct wined3d_surface* surface; } ;
struct TYPE_5__ {TYPE_1__ u; } ;

/* Variables and functions */

__attribute__((used)) static inline struct wined3d_surface *context_get_rt_surface(const struct wined3d_context *context)
{
    struct wined3d_texture *texture = context->current_rt.texture;

    if (!texture)
        return NULL;
    return texture->sub_resources[context->current_rt.sub_resource_idx].u.surface;
}