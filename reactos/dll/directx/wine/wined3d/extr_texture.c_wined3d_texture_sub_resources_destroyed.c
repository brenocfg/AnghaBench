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
struct wined3d_texture_sub_resource {int /*<<< orphan*/ * parent; TYPE_1__* parent_ops; } ;
struct wined3d_texture {unsigned int level_count; unsigned int layer_count; struct wined3d_texture_sub_resource* sub_resources; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wined3d_object_destroyed ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wined3d_texture_sub_resources_destroyed(struct wined3d_texture *texture)
{
    unsigned int sub_count = texture->level_count * texture->layer_count;
    struct wined3d_texture_sub_resource *sub_resource;
    unsigned int i;

    for (i = 0; i < sub_count; ++i)
    {
        sub_resource = &texture->sub_resources[i];
        if (sub_resource->parent)
        {
            TRACE("sub-resource %u.\n", i);
            sub_resource->parent_ops->wined3d_object_destroyed(sub_resource->parent);
            sub_resource->parent = NULL;
        }
    }
}