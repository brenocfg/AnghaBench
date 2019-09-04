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
typedef  int uint8 ;

/* Variables and functions */

__attribute__((used)) static void
process_compressed_8x8_brush_data(uint8 * in, uint8 * out, int Bpp)
{
	int x, y, pal_index, in_index, shift, do2, i;
	uint8 *pal;

	in_index = 0;
	pal = in + 16;
	/* read it bottom up */
	for (y = 7; y >= 0; y--)
	{
		/* 2 bytes per row */
		x = 0;
		for (do2 = 0; do2 < 2; do2++)
		{
			/* 4 pixels per byte */
			shift = 6;
			while (shift >= 0)
			{
				pal_index = (in[in_index] >> shift) & 3;
				/* size of palette entries depends on Bpp */
				for (i = 0; i < Bpp; i++)
				{
					out[(y * 8 + x) * Bpp + i] = pal[pal_index * Bpp + i];
				}
				x++;
				shift -= 2;
			}
			in_index++;
		}
	}
}