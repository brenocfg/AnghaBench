#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ gs_shader_t ;
struct TYPE_9__ {TYPE_1__* cur_pixel_shader; } ;
typedef  TYPE_2__ gs_device_t ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PIXEL ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_textures (TYPE_2__*) ; 
 int /*<<< orphan*/  load_default_pixelshader_samplers (TYPE_2__*,TYPE_1__*) ; 

void device_load_pixelshader(gs_device_t *device, gs_shader_t *pixelshader)
{
	if (device->cur_pixel_shader == pixelshader)
		return;

	if (pixelshader && pixelshader->type != GS_SHADER_PIXEL) {
		blog(LOG_ERROR, "Specified shader is not a pixel shader");
		goto fail;
	}

	device->cur_pixel_shader = pixelshader;

	clear_textures(device);

	if (pixelshader)
		load_default_pixelshader_samplers(device, pixelshader);
	return;

fail:
	blog(LOG_ERROR, "device_load_pixelshader (GL) failed");
}