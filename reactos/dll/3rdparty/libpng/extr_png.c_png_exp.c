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
typedef  int png_uint_32 ;
typedef  int png_fixed_point ;

/* Variables and functions */
 int* png_32bit_exp ; 

__attribute__((used)) static png_uint_32
png_exp(png_fixed_point x)
{
   if (x > 0 && x <= 0xfffff) /* Else overflow or zero (underflow) */
   {
      /* Obtain a 4-bit approximation */
      png_uint_32 e = png_32bit_exp[(x >> 12) & 0x0f];

      /* Incorporate the low 12 bits - these decrease the returned value by
       * multiplying by a number less than 1 if the bit is set.  The multiplier
       * is determined by the above table and the shift. Notice that the values
       * converge on 45426 and this is used to allow linear interpolation of the
       * low bits.
       */
      if (x & 0x800)
         e -= (((e >> 16) * 44938U) +  16U) >> 5;

      if (x & 0x400)
         e -= (((e >> 16) * 45181U) +  32U) >> 6;

      if (x & 0x200)
         e -= (((e >> 16) * 45303U) +  64U) >> 7;

      if (x & 0x100)
         e -= (((e >> 16) * 45365U) + 128U) >> 8;

      if (x & 0x080)
         e -= (((e >> 16) * 45395U) + 256U) >> 9;

      if (x & 0x040)
         e -= (((e >> 16) * 45410U) + 512U) >> 10;

      /* And handle the low 6 bits in a single block. */
      e -= (((e >> 16) * 355U * (x & 0x3fU)) + 256U) >> 9;

      /* Handle the upper bits of x. */
      e >>= x >> 16;
      return e;
   }

   /* Check for overflow */
   if (x <= 0)
      return png_32bit_exp[0];

   /* Else underflow */
   return 0;
}