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
struct gs_device {int /*<<< orphan*/  copy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_TYPE_ARB ; 
 int /*<<< orphan*/  COPY_TYPE_FBO_BLIT ; 
 int /*<<< orphan*/  COPY_TYPE_NV ; 
 scalar_t__ GLAD_GL_ARB_copy_image ; 
 scalar_t__ GLAD_GL_NV_copy_image ; 
 int /*<<< orphan*/  GLAD_GL_VERSION_3_3 ; 
 scalar_t__ GLAD_GL_VERSION_4_3 ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_SEAMLESS ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_enable_debug () ; 

__attribute__((used)) static bool gl_init_extensions(struct gs_device *device)
{
	if (!GLAD_GL_VERSION_3_3) {
		blog(LOG_ERROR,
		     "obs-studio requires OpenGL version 3.3 or higher.");
		return false;
	}

	gl_enable_debug();

	gl_enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	if (GLAD_GL_VERSION_4_3 || GLAD_GL_ARB_copy_image)
		device->copy_type = COPY_TYPE_ARB;
	else if (GLAD_GL_NV_copy_image)
		device->copy_type = COPY_TYPE_NV;
	else
		device->copy_type = COPY_TYPE_FBO_BLIT;

	return true;
}