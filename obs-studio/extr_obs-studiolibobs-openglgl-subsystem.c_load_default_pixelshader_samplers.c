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
struct TYPE_2__ {size_t num; struct gs_sampler_state** array; } ;
struct gs_shader {TYPE_1__ samplers; } ;
struct gs_sampler_state {int dummy; } ;
struct gs_device {struct gs_sampler_state** cur_samplers; } ;

/* Variables and functions */
 size_t GS_MAX_TEXTURES ; 

__attribute__((used)) static void load_default_pixelshader_samplers(struct gs_device *device,
		struct gs_shader *ps)
{
	size_t i;
	if (!ps)
		return;

	for (i = 0; i < ps->samplers.num; i++) {
		struct gs_sampler_state *ss = ps->samplers.array[i];
		device->cur_samplers[i] = ss;
	}

	for (; i < GS_MAX_TEXTURES; i++)
		device->cur_samplers[i] = NULL;
}