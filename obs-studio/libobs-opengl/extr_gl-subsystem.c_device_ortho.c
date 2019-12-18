#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float x; float y; float z; float w; } ;
struct matrix4 {TYPE_2__ t; TYPE_2__ z; TYPE_2__ y; TYPE_2__ x; } ;
struct TYPE_4__ {struct matrix4 cur_proj; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  vec4_zero (TYPE_2__*) ; 

void device_ortho(gs_device_t *device, float left, float right, float top,
		  float bottom, float near, float far)
{
	struct matrix4 *dst = &device->cur_proj;

	float rml = right - left;
	float bmt = bottom - top;
	float fmn = far - near;

	vec4_zero(&dst->x);
	vec4_zero(&dst->y);
	vec4_zero(&dst->z);
	vec4_zero(&dst->t);

	dst->x.x = 2.0f / rml;
	dst->t.x = (left + right) / -rml;

	dst->y.y = 2.0f / -bmt;
	dst->t.y = (bottom + top) / bmt;

	dst->z.z = -2.0f / fmn;
	dst->t.z = (far + near) / -fmn;

	dst->t.w = 1.0f;
}