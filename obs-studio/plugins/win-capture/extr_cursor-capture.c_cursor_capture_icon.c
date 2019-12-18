#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct cursor_data {scalar_t__ last_cx; scalar_t__ last_cy; int /*<<< orphan*/  texture; int /*<<< orphan*/  y_hotspot; int /*<<< orphan*/  x_hotspot; } ;
struct TYPE_4__ {int /*<<< orphan*/  hbmMask; int /*<<< orphan*/  hbmColor; int /*<<< orphan*/  yHotspot; int /*<<< orphan*/  xHotspot; } ;
typedef  TYPE_1__ ICONINFO ;
typedef  int /*<<< orphan*/  HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIconInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cursor_capture_icon_bitmap (TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  get_cached_texture (struct cursor_data*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_texture_set_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static inline bool cursor_capture_icon(struct cursor_data *data, HICON icon)
{
	uint8_t *bitmap;
	uint32_t height;
	uint32_t width;
	ICONINFO ii;

	if (!icon) {
		return false;
	}
	if (!GetIconInfo(icon, &ii)) {
		return false;
	}

	bitmap = cursor_capture_icon_bitmap(&ii, &width, &height);
	if (bitmap) {
		if (data->last_cx != width || data->last_cy != height) {
			data->texture = get_cached_texture(data, width, height);
			data->last_cx = width;
			data->last_cy = height;
		}
		gs_texture_set_image(data->texture, bitmap, width * 4, false);
		bfree(bitmap);

		data->x_hotspot = ii.xHotspot;
		data->y_hotspot = ii.yHotspot;
	}

	DeleteObject(ii.hbmColor);
	DeleteObject(ii.hbmMask);
	return !!data->texture;
}