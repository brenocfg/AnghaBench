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
typedef  scalar_t__* png_const_charp ;

/* Variables and functions */
 scalar_t__ png_check_fp_number (scalar_t__*,size_t,int*,size_t*) ; 

int
png_check_fp_string(png_const_charp string, size_t size)
{
   int        state=0;
   size_t char_index=0;

   if (png_check_fp_number(string, size, &state, &char_index) != 0 &&
      (char_index == size || string[char_index] == 0))
      return state /* must be non-zero - see above */;

   return 0; /* i.e. fail */
}