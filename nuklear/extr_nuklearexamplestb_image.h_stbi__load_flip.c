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
typedef  unsigned char stbi_uc ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 unsigned char* stbi__load_main (int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 scalar_t__ stbi__vertically_flip_on_load ; 

__attribute__((used)) static unsigned char *stbi__load_flip(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *result = stbi__load_main(s, x, y, comp, req_comp);

   if (stbi__vertically_flip_on_load && result != NULL) {
      int w = *x, h = *y;
      int depth = req_comp ? req_comp : *comp;
      int row,col,z;
      stbi_uc temp;

      // @OPTIMIZE: use a bigger temp buffer and memcpy multiple pixels at once
      for (row = 0; row < (h>>1); row++) {
         for (col = 0; col < w; col++) {
            for (z = 0; z < depth; z++) {
               temp = result[(row * w + col) * depth + z];
               result[(row * w + col) * depth + z] = result[((h - row - 1) * w + col) * depth + z];
               result[((h - row - 1) * w + col) * depth + z] = temp;
            }
         }
      }
   }

   return result;
}