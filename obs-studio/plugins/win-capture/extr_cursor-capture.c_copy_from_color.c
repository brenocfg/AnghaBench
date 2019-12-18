#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  long uint32_t ;
struct TYPE_6__ {int bmBitsPixel; long bmHeight; long bmWidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbmMask; int /*<<< orphan*/  hbmColor; } ;
typedef  TYPE_1__ ICONINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  apply_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_has_alpha (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/ * get_bitmap_data (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline uint8_t *copy_from_color(ICONINFO *ii, uint32_t *width,
				       uint32_t *height)
{
	BITMAP bmp_color;
	BITMAP bmp_mask;
	uint8_t *color;
	uint8_t *mask;

	color = get_bitmap_data(ii->hbmColor, &bmp_color);
	if (!color) {
		return NULL;
	}

	if (bmp_color.bmBitsPixel < 32) {
		bfree(color);
		return NULL;
	}

	mask = get_bitmap_data(ii->hbmMask, &bmp_mask);
	if (mask) {
		long pixels = bmp_color.bmHeight * bmp_color.bmWidth;

		if (!bitmap_has_alpha(color, pixels))
			apply_mask(color, mask, pixels);

		bfree(mask);
	}

	*width = bmp_color.bmWidth;
	*height = bmp_color.bmHeight;
	return color;
}