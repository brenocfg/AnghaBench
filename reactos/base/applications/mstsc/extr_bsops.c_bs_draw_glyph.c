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

/* Variables and functions */
 scalar_t__ bs_is_pixel_on (char*,int,int,int,int) ; 
 int /*<<< orphan*/  bs_set_pixel (int,int,int,int,int) ; 

void
bs_draw_glyph(int x, int y, char * glyph_data, int glyph_width,
              int glyph_height, int fgcolour)
{
  int i;
  int j;

  for (i = 0; i < glyph_height; i++)
  {
    for (j = 0; j < glyph_width; j++)
    {
      if (bs_is_pixel_on(glyph_data, j, i, glyph_width, 8))
      {
        bs_set_pixel(x + j, y + i, fgcolour, 12, 1);
      }
    }
  }
}