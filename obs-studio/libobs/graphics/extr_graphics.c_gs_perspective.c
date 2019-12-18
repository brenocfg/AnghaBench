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
struct TYPE_4__ {int /*<<< orphan*/  (* device_frustum ) (int /*<<< orphan*/ ,float,float,float,float,float,float) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 float RAD (float) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,float,float,float,float,float,float) ; 
 float tanf (float) ; 
 TYPE_2__* thread_graphics ; 

void gs_perspective(float angle, float aspect, float near, float far)
{
	graphics_t *graphics = thread_graphics;
	float xmin, xmax, ymin, ymax;

	if (!gs_valid("gs_perspective"))
		return;

	ymax = near * tanf(RAD(angle) * 0.5f);
	ymin = -ymax;

	xmin = ymin * aspect;
	xmax = ymax * aspect;

	graphics->exports.device_frustum(graphics->device, xmin, xmax, ymin,
					 ymax, near, far);
}