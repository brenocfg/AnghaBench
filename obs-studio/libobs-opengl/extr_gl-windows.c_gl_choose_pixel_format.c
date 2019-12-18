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
struct gs_init_data {int /*<<< orphan*/  zsformat; int /*<<< orphan*/  format; } ;
struct darray {int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GL_TRUE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  WGL_ACCELERATION_ARB ; 
 int /*<<< orphan*/  WGL_COLOR_BITS_ARB ; 
 int /*<<< orphan*/  WGL_DEPTH_BITS_ARB ; 
 int /*<<< orphan*/  WGL_DOUBLE_BUFFER_ARB ; 
 int /*<<< orphan*/  WGL_DRAW_TO_WINDOW_ARB ; 
 int WGL_FULL_ACCELERATION_ARB ; 
 int /*<<< orphan*/  WGL_PIXEL_TYPE_ARB ; 
 int /*<<< orphan*/  WGL_STENCIL_BITS_ARB ; 
 int /*<<< orphan*/  WGL_SUPPORT_OPENGL_ARB ; 
 int WGL_TYPE_RGBA_ARB ; 
 int /*<<< orphan*/  add_attrib (struct darray*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  darray_free (struct darray*) ; 
 int /*<<< orphan*/  darray_init (struct darray*) ; 
 int get_color_format_bits (int /*<<< orphan*/ ) ; 
 int get_depth_format_bits (int /*<<< orphan*/ ) ; 
 int get_stencil_format_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglChoosePixelFormatARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gl_choose_pixel_format(HDC hdc, const struct gs_init_data *info)
{
	struct darray attribs;
	int color_bits = get_color_format_bits(info->format);
	int depth_bits = get_depth_format_bits(info->zsformat);
	int stencil_bits = get_stencil_format_bits(info->zsformat);
	UINT num_formats;
	BOOL success;
	int format;

	if (!color_bits) {
		blog(LOG_ERROR, "gl_init_pixel_format: color format not "
				"supported");
		return false;
	}

	darray_init(&attribs);
	add_attrib(&attribs, WGL_DRAW_TO_WINDOW_ARB, GL_TRUE);
	add_attrib(&attribs, WGL_SUPPORT_OPENGL_ARB, GL_TRUE);
	add_attrib(&attribs, WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB);
	add_attrib(&attribs, WGL_DOUBLE_BUFFER_ARB, GL_TRUE);
	add_attrib(&attribs, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB);
	add_attrib(&attribs, WGL_COLOR_BITS_ARB, color_bits);
	add_attrib(&attribs, WGL_DEPTH_BITS_ARB, depth_bits);
	add_attrib(&attribs, WGL_STENCIL_BITS_ARB, stencil_bits);
	add_attrib(&attribs, 0, 0);

	success = wglChoosePixelFormatARB(hdc, attribs.array, NULL, 1, &format,
					  &num_formats);
	if (!success || !num_formats) {
		blog(LOG_ERROR, "wglChoosePixelFormatARB failed, %lu",
		     GetLastError());
		format = 0;
	}

	darray_free(&attribs);

	return format;
}