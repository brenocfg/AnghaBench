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
struct d3d_light {int /*<<< orphan*/  light7; int /*<<< orphan*/  dwLightIndex; TYPE_1__* active_viewport; } ;
struct d3d_device {int /*<<< orphan*/  IDirect3DDevice7_iface; } ;
struct TYPE_2__ {struct d3d_device* active_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice7_SetLight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3d_light*) ; 

__attribute__((used)) static void light_update(struct d3d_light *light)
{
    struct d3d_device *device;

    TRACE("light %p.\n", light);

    if (!light->active_viewport || !light->active_viewport->active_device) return;
    device = light->active_viewport->active_device;

    IDirect3DDevice7_SetLight(&device->IDirect3DDevice7_iface, light->dwLightIndex, &light->light7);
}