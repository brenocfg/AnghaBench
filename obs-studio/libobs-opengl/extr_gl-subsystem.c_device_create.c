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
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_device {int /*<<< orphan*/ * cur_swap; int /*<<< orphan*/  empty_vao; int /*<<< orphan*/  plat; } ;
typedef  struct gs_device gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 int /*<<< orphan*/  GL_SHADING_LANGUAGE_VERSION ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int GS_ERROR_FAIL ; 
 int GS_ERROR_NOT_SUPPORTED ; 
 int GS_SUCCESS ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  bfree (struct gs_device*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 struct gs_device* bzalloc (int) ; 
 int /*<<< orphan*/  device_leave_context (struct gs_device*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_gen_vertex_arrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_init_extensions (struct gs_device*) ; 
 int /*<<< orphan*/  gl_platform_create (struct gs_device*,int /*<<< orphan*/ ) ; 

int device_create(gs_device_t **p_device, uint32_t adapter)
{
	struct gs_device *device = bzalloc(sizeof(struct gs_device));
	int errorcode = GS_ERROR_FAIL;

	blog(LOG_INFO, "---------------------------------");
	blog(LOG_INFO, "Initializing OpenGL...");

	device->plat = gl_platform_create(device, adapter);
	if (!device->plat)
		goto fail;

	const char *glVendor = (const char *)glGetString(GL_VENDOR);
	const char *glRenderer = (const char *)glGetString(GL_RENDERER);

	blog(LOG_INFO, "Loading up OpenGL on adapter %s %s", glVendor,
	     glRenderer);

	if (!gl_init_extensions(device)) {
		errorcode = GS_ERROR_NOT_SUPPORTED;
		goto fail;
	}

	const char *glVersion = (const char *)glGetString(GL_VERSION);
	const char *glShadingLanguage =
		(const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);

	blog(LOG_INFO,
	     "OpenGL loaded successfully, version %s, shading "
	     "language %s",
	     glVersion, glShadingLanguage);

	gl_enable(GL_CULL_FACE);
	gl_gen_vertex_arrays(1, &device->empty_vao);

	device_leave_context(device);
	device->cur_swap = NULL;

#ifdef _WIN32
	blog(LOG_INFO, "Warning: The OpenGL renderer is currently in use.  "
		       "On windows, the OpenGL renderer can decrease "
		       "capture performance due to the lack of specific "
		       "features used to maximize capture performance.  "
		       "The Direct3D 11 renderer is recommended instead.");
#endif

	*p_device = device;
	return GS_SUCCESS;

fail:
	blog(LOG_ERROR, "device_create (GL) failed");
	bfree(device);

	*p_device = NULL;
	return errorcode;
}