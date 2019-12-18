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
 int STBI_grey ; 
 int STBI_grey_alpha ; 
 int STBI_rgb ; 

__attribute__((used)) static int stbi__tga_get_comp(int bits_per_pixel, int is_grey, int* is_rgb16)
{
   // only RGB or RGBA (incl. 16bit) or grey allowed
   if(is_rgb16) *is_rgb16 = 0;
   switch(bits_per_pixel) {
      case 8:  return STBI_grey;
      case 16: if(is_grey) return STBI_grey_alpha;
            // else: fall-through
      case 15: if(is_rgb16) *is_rgb16 = 1;
            return STBI_rgb;
      case 24: // fall-through
      case 32: return bits_per_pixel/8;
      default: return 0;
   }
}