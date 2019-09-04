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

int
bs_is_pixel_on(char * data, int x, int y, int width, int bpp)
{
  int start;
  int shift;

  if (bpp == 1)
  {
    width = (width + 7) / 8;
    start = (y * width) + x / 8;
    shift = x % 8;
    return (data[start] & (0x80 >> shift)) != 0;
  }
  else if (bpp == 8)
  {
    return data[y * width + x] != 0;
  }
  else if (bpp == 15 || bpp == 16)
  {
    return data[(y * 2) * width + (x * 2)] != 0 ||
           data[(y * 2) * width + (x * 2) + 1] != 0;
  }
  else if (bpp == 24 || bpp == 32)
  {
    return data[(y * 4) * width + (x * 4)] != 0 ||
           data[(y * 4) * width + (x * 4) + 1] != 0 ||
           data[(y * 4) * width + (x * 4) + 2] != 0 ||
           data[(y * 4) * width + (x * 4) + 3] != 0;
  }
  else
  {
    return 0;
  }
}