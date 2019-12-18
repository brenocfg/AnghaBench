#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_fast32_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int width; int height; int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ XFixesCursorImage ;

/* Variables and functions */
 scalar_t__* bmalloc (int) ; 

__attribute__((used)) static uint32_t *xcursor_pixels(XFixesCursorImage *xc)
{
	uint_fast32_t size = xc->width * xc->height;
	uint32_t *pixels = bmalloc(size * sizeof(uint32_t));

	for (uint_fast32_t i = 0; i < size; ++i)
		pixels[i] = (uint32_t)xc->pixels[i];

	return pixels;
}