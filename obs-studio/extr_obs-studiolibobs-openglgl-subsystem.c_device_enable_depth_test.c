#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_enable (int /*<<< orphan*/ ) ; 

void device_enable_depth_test(gs_device_t *device, bool enable)
{
	if (enable)
		gl_enable(GL_DEPTH_TEST);
	else
		gl_disable(GL_DEPTH_TEST);

	UNUSED_PARAMETER(device);
}