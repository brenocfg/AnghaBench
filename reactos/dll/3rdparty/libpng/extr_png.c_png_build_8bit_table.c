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
typedef  int /*<<< orphan*/  png_structrp ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  scalar_t__** png_bytepp ;
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;

/* Variables and functions */
 scalar_t__ png_gamma_8bit_correct (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ png_gamma_significant (int /*<<< orphan*/ ) ; 
 scalar_t__ png_malloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
png_build_8bit_table(png_structrp png_ptr, png_bytepp ptable,
    png_fixed_point gamma_val)
{
   unsigned int i;
   png_bytep table = *ptable = (png_bytep)png_malloc(png_ptr, 256);

   if (png_gamma_significant(gamma_val) != 0)
      for (i=0; i<256; i++)
         table[i] = png_gamma_8bit_correct(i, gamma_val);

   else
      for (i=0; i<256; ++i)
         table[i] = (png_byte)(i & 0xff);
}