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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct vec4 {int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  int /*<<< orphan*/  GLbitfield ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_STENCIL_BUFFER_BIT ; 
 int GS_CLEAR_COLOR ; 
 int GS_CLEAR_DEPTH ; 
 int GS_CLEAR_STENCIL ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearDepth (float) ; 
 int /*<<< orphan*/  glClearStencil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_clear(gs_device_t *device, uint32_t clear_flags,
		  const struct vec4 *color, float depth, uint8_t stencil)
{
	GLbitfield gl_flags = 0;

	if (clear_flags & GS_CLEAR_COLOR) {
		glClearColor(color->x, color->y, color->z, color->w);
		gl_flags |= GL_COLOR_BUFFER_BIT;
	}

	if (clear_flags & GS_CLEAR_DEPTH) {
		glClearDepth(depth);
		gl_flags |= GL_DEPTH_BUFFER_BIT;
	}

	if (clear_flags & GS_CLEAR_STENCIL) {
		glClearStencil(stencil);
		gl_flags |= GL_STENCIL_BUFFER_BIT;
	}

	glClear(gl_flags);
	if (!gl_success("glClear"))
		blog(LOG_ERROR, "device_clear (GL) failed");

	UNUSED_PARAMETER(device);
}