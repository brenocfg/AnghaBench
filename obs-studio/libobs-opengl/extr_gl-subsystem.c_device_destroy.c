#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  plat; int /*<<< orphan*/  proj_stack; int /*<<< orphan*/  empty_vao; scalar_t__ first_program; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_delete_vertex_arrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_platform_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_program_destroy (scalar_t__) ; 

void device_destroy(gs_device_t *device)
{
	if (device) {
		while (device->first_program)
			gs_program_destroy(device->first_program);

		gl_delete_vertex_arrays(1, &device->empty_vao);

		da_free(device->proj_stack);
		gl_platform_destroy(device->plat);
		bfree(device);
	}
}