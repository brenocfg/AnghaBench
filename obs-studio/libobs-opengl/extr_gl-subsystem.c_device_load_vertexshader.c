#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ gs_shader_t ;
struct TYPE_6__ {TYPE_1__* cur_vertex_shader; } ;
typedef  TYPE_2__ gs_device_t ;

/* Variables and functions */
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

void device_load_vertexshader(gs_device_t *device, gs_shader_t *vertshader)
{
	if (device->cur_vertex_shader == vertshader)
		return;

	if (vertshader && vertshader->type != GS_SHADER_VERTEX) {
		blog(LOG_ERROR, "Specified shader is not a vertex shader");
		blog(LOG_ERROR, "device_load_vertexshader (GL) failed");
		return;
	}

	device->cur_vertex_shader = vertshader;
}