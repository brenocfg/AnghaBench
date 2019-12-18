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
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_row_infop ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_3__ {int bit_depth; scalar_t__ width; scalar_t__ channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_do_swap(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_swap\n");
   if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL &&
#endif
       row_info->bit_depth == 16)
   {
      png_bytep rp = row;
      png_uint_32 i;
      png_uint_32 istop= row_info->width * row_info->channels;

      for (i = 0; i < istop; i++, rp += 2)
      {
         png_byte t = *rp;
         *rp = *(rp + 1);
         *(rp + 1) = t;
      }
   }
}