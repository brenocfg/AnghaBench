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
struct gs_init_data {int dummy; } ;
struct gl_windowinfo {int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_getpixelformat (int /*<<< orphan*/ ,struct gs_init_data const*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_setpixelformat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct gl_windowinfo* gl_windowinfo_bare (struct gs_init_data const*) ; 
 int /*<<< orphan*/  gl_windowinfo_destroy (struct gl_windowinfo*) ; 

struct gl_windowinfo *gl_windowinfo_create(const struct gs_init_data *info)
{
	struct gl_windowinfo *wi = gl_windowinfo_bare(info);
	PIXELFORMATDESCRIPTOR pfd;
	int pixel_format;

	if (!wi)
		return NULL;

	if (!gl_getpixelformat(wi->hdc, info, &pixel_format, &pfd))
		goto fail;
	if (!gl_setpixelformat(wi->hdc, pixel_format, &pfd))
		goto fail;

	return wi;

fail:
	blog(LOG_ERROR, "gl_windowinfo_create failed");
	gl_windowinfo_destroy(wi);
	return NULL;
}