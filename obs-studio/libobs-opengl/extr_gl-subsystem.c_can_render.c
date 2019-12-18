#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  cur_render_target; int /*<<< orphan*/  cur_swap; int /*<<< orphan*/  cur_vertex_buffer; int /*<<< orphan*/  cur_pixel_shader; int /*<<< orphan*/  cur_vertex_shader; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool can_render(const gs_device_t *device, uint32_t num_verts)
{
	if (!device->cur_vertex_shader) {
		blog(LOG_ERROR, "No vertex shader specified");
		return false;
	}

	if (!device->cur_pixel_shader) {
		blog(LOG_ERROR, "No pixel shader specified");
		return false;
	}

	if (!device->cur_vertex_buffer && (num_verts == 0)) {
		blog(LOG_ERROR, "No vertex buffer specified");
		return false;
	}

	if (!device->cur_swap && !device->cur_render_target) {
		blog(LOG_ERROR, "No active swap chain or render target");
		return false;
	}

	return true;
}