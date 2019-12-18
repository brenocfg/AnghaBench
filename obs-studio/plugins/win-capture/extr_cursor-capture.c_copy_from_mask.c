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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int bmHeight; long bmWidth; long bmWidthBytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbmMask; } ;
typedef  TYPE_1__ ICONINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__*) ; 
 scalar_t__ bit_to_alpha (scalar_t__*,long,int) ; 
 scalar_t__* bzalloc (long) ; 
 scalar_t__* get_bitmap_data (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline uint8_t *copy_from_mask(ICONINFO *ii, uint32_t *width,
				      uint32_t *height)
{
	uint8_t *output;
	uint8_t *mask;
	long pixels;
	long bottom;
	BITMAP bmp;

	mask = get_bitmap_data(ii->hbmMask, &bmp);
	if (!mask) {
		return NULL;
	}

	bmp.bmHeight /= 2;

	pixels = bmp.bmHeight * bmp.bmWidth;
	output = bzalloc(pixels * 4);

	bottom = bmp.bmWidthBytes * bmp.bmHeight;

	for (long i = 0; i < pixels; i++) {
		uint8_t alpha = bit_to_alpha(mask, i, false);
		uint8_t color = bit_to_alpha(mask + bottom, i, true);

		if (!alpha) {
			output[i * 4 + 3] = color;
		} else {
			*(uint32_t *)&output[i * 4] = !!color ? 0xFFFFFFFF
							      : 0xFF000000;
		}
	}

	bfree(mask);

	*width = bmp.bmWidth;
	*height = bmp.bmHeight;
	return output;
}