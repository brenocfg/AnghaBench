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
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DescribePixelFormat (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gl_choose_pixel_format (int /*<<< orphan*/ ,struct gs_init_data const*) ; 

__attribute__((used)) static inline bool gl_getpixelformat(HDC hdc, const struct gs_init_data *info,
				     int *format, PIXELFORMATDESCRIPTOR *pfd)
{
	if (!format)
		return false;

	*format = gl_choose_pixel_format(hdc, info);

	if (!DescribePixelFormat(hdc, *format, sizeof(*pfd), pfd)) {
		blog(LOG_ERROR, "DescribePixelFormat failed, %lu",
		     GetLastError());
		return false;
	}

	return true;
}