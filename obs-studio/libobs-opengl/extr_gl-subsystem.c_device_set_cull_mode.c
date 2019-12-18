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
struct TYPE_3__ {int cur_cull_mode; } ;
typedef  TYPE_1__ gs_device_t ;
typedef  enum gs_cull_mode { ____Placeholder_gs_cull_mode } gs_cull_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int GS_BACK ; 
 int GS_FRONT ; 
 scalar_t__ GS_NEITHER ; 
 int /*<<< orphan*/  gl_cull_face (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_enable (int /*<<< orphan*/ ) ; 

void device_set_cull_mode(gs_device_t *device, enum gs_cull_mode mode)
{
	if (device->cur_cull_mode == mode)
		return;

	if (device->cur_cull_mode == GS_NEITHER)
		gl_enable(GL_CULL_FACE);

	device->cur_cull_mode = mode;

	if (mode == GS_BACK)
		gl_cull_face(GL_BACK);
	else if (mode == GS_FRONT)
		gl_cull_face(GL_FRONT);
	else
		gl_disable(GL_CULL_FACE);
}