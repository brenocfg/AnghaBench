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
struct gs_rect {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gl_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ gl_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ gl_success (char*) ; 

void device_set_scissor_rect(gs_device_t *device, const struct gs_rect *rect)
{
	UNUSED_PARAMETER(device);

	if (rect != NULL) {
		glScissor(rect->x, rect->y, rect->cx, rect->cy);
		if (gl_success("glScissor") && gl_enable(GL_SCISSOR_TEST))
			return;

	} else if (gl_disable(GL_SCISSOR_TEST)) {
		return;
	}

	blog(LOG_ERROR, "device_set_scissor_rect (GL) failed");
}