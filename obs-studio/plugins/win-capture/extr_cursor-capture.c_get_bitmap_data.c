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
struct TYPE_4__ {int bmHeight; int bmWidth; int bmBitsPixel; } ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  GetBitmapBits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetObject (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * bmalloc (unsigned int) ; 

__attribute__((used)) static uint8_t *get_bitmap_data(HBITMAP hbmp, BITMAP *bmp)
{
	if (GetObject(hbmp, sizeof(*bmp), bmp) != 0) {
		uint8_t *output;
		unsigned int size =
			(bmp->bmHeight * bmp->bmWidth * bmp->bmBitsPixel) / 8;

		output = bmalloc(size);
		GetBitmapBits(hbmp, size, output);
		return output;
	}

	return NULL;
}