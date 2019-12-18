#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct dc_capture {int x; int y; int capture_cursor; int compatibility; int /*<<< orphan*/  bmp; int /*<<< orphan*/  hdc; int /*<<< orphan*/  old_bmp; int /*<<< orphan*/  bits; int /*<<< orphan*/  valid; void* height; void* width; } ;
struct TYPE_4__ {int biSize; int biBitCount; int biPlanes; void* biHeight; void* biWidth; } ;
struct TYPE_5__ {TYPE_1__ bmiHeader; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_gdi_texture_available () ; 
 int /*<<< orphan*/  init_textures (struct dc_capture*) ; 
 int /*<<< orphan*/  memset (struct dc_capture*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

void dc_capture_init(struct dc_capture *capture, int x, int y, uint32_t width,
		     uint32_t height, bool cursor, bool compatibility)
{
	memset(capture, 0, sizeof(struct dc_capture));

	capture->x = x;
	capture->y = y;
	capture->width = width;
	capture->height = height;
	capture->capture_cursor = cursor;

	obs_enter_graphics();

	if (!gs_gdi_texture_available())
		compatibility = true;

	capture->compatibility = compatibility;

	init_textures(capture);

	obs_leave_graphics();

	if (!capture->valid)
		return;

	if (compatibility) {
		BITMAPINFO bi = {0};
		BITMAPINFOHEADER *bih = &bi.bmiHeader;
		bih->biSize = sizeof(BITMAPINFOHEADER);
		bih->biBitCount = 32;
		bih->biWidth = width;
		bih->biHeight = height;
		bih->biPlanes = 1;

		capture->hdc = CreateCompatibleDC(NULL);
		capture->bmp =
			CreateDIBSection(capture->hdc, &bi, DIB_RGB_COLORS,
					 (void **)&capture->bits, NULL, 0);
		capture->old_bmp = SelectObject(capture->hdc, capture->bmp);
	}
}