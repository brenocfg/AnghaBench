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
typedef  float const gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEBUG_SOURCE_APPLICATION ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (float const*) ; 
 int /*<<< orphan*/  glPushDebugGroupKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

void device_debug_marker_begin(gs_device_t *device, const char *markername,
			       const float color[4])
{
	UNUSED_PARAMETER(device);
	UNUSED_PARAMETER(color);

	glPushDebugGroupKHR(GL_DEBUG_SOURCE_APPLICATION, 0, -1, markername);
}