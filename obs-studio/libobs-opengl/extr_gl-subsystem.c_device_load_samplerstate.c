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
typedef  int /*<<< orphan*/  gs_samplerstate_t ;
struct TYPE_4__ {int /*<<< orphan*/ ** cur_samplers; int /*<<< orphan*/  cur_pixel_shader; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  load_sampler_on_textures (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void device_load_samplerstate(gs_device_t *device, gs_samplerstate_t *ss,
			      int unit)
{
	/* need a pixel shader to properly bind samplers */
	if (!device->cur_pixel_shader)
		ss = NULL;

	if (device->cur_samplers[unit] == ss)
		return;

	device->cur_samplers[unit] = ss;

	if (!ss)
		return;

	if (!load_sampler_on_textures(device, ss, unit))
		blog(LOG_ERROR, "device_load_samplerstate (GL) failed");

	return;
}