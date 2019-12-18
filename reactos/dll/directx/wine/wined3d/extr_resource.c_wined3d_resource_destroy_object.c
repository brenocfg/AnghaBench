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
struct wined3d_resource {int /*<<< orphan*/  type; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_resource_released (int /*<<< orphan*/ ,struct wined3d_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_free_sysmem (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_resource_release (struct wined3d_resource*) ; 

__attribute__((used)) static void wined3d_resource_destroy_object(void *object)
{
    struct wined3d_resource *resource = object;

    wined3d_resource_free_sysmem(resource);
    context_resource_released(resource->device, resource, resource->type);
    wined3d_resource_release(resource);
}