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
typedef  char* png_const_charp ;
typedef  char* png_charp ;
typedef  scalar_t__ png_alloc_size_t ;

/* Variables and functions */
#define  PNG_NUMBER_FORMAT_02u 132 
#define  PNG_NUMBER_FORMAT_02x 131 
#define  PNG_NUMBER_FORMAT_fixed 130 
#define  PNG_NUMBER_FORMAT_u 129 
#define  PNG_NUMBER_FORMAT_x 128 

png_charp
png_format_number(png_const_charp start, png_charp end, int format,
    png_alloc_size_t number)
{
   int count = 0;    /* number of digits output */
   int mincount = 1; /* minimum number required */
   int output = 0;   /* digit output (for the fixed point format) */

   *--end = '\0';

   /* This is written so that the loop always runs at least once, even with
    * number zero.
    */
   while (end > start && (number != 0 || count < mincount))
   {

      static const char digits[] = "0123456789ABCDEF";

      switch (format)
      {
         case PNG_NUMBER_FORMAT_fixed:
            /* Needs five digits (the fraction) */
            mincount = 5;
            if (output != 0 || number % 10 != 0)
            {
               *--end = digits[number % 10];
               output = 1;
            }
            number /= 10;
            break;

         case PNG_NUMBER_FORMAT_02u:
            /* Expects at least 2 digits. */
            mincount = 2;
            /* FALLTHROUGH */

         case PNG_NUMBER_FORMAT_u:
            *--end = digits[number % 10];
            number /= 10;
            break;

         case PNG_NUMBER_FORMAT_02x:
            /* This format expects at least two digits */
            mincount = 2;
            /* FALLTHROUGH */

         case PNG_NUMBER_FORMAT_x:
            *--end = digits[number & 0xf];
            number >>= 4;
            break;

         default: /* an error */
            number = 0;
            break;
      }

      /* Keep track of the number of digits added */
      ++count;

      /* Float a fixed number here: */
      if ((format == PNG_NUMBER_FORMAT_fixed) && (count == 5) && (end > start))
      {
         /* End of the fraction, but maybe nothing was output?  In that case
          * drop the decimal point.  If the number is a true zero handle that
          * here.
          */
         if (output != 0)
            *--end = '.';
         else if (number == 0) /* and !output */
            *--end = '0';
      }
   }

   return end;
}