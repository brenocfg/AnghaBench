#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  TYPE_2__* png_row_infop ;
struct TYPE_7__ {scalar_t__ rowbytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  row_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_write_filtered_row (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_write_find_filter(png_structrp png_ptr, png_row_infop row_info)
{
#ifndef PNG_WRITE_FILTER_SUPPORTED
   png_write_filtered_row(png_ptr, png_ptr->row_buf, row_info->rowbytes+1);
#else
   unsigned int filter_to_do = png_ptr->do_filter;
   png_bytep row_buf;
   png_bytep best_row;
   png_uint_32 bpp;
   size_t mins;
   size_t row_bytes = row_info->rowbytes;

   png_debug(1, "in png_write_find_filter");

   /* Find out how many bytes offset each pixel is */
   bpp = (row_info->pixel_depth + 7) >> 3;

   row_buf = png_ptr->row_buf;
   mins = PNG_SIZE_MAX - 256/* so we can detect potential overflow of the
                               running sum */;

   /* The prediction method we use is to find which method provides the
    * smallest value when summing the absolute values of the distances
    * from zero, using anything >= 128 as negative numbers.  This is known
    * as the "minimum sum of absolute differences" heuristic.  Other
    * heuristics are the "weighted minimum sum of absolute differences"
    * (experimental and can in theory improve compression), and the "zlib
    * predictive" method (not implemented yet), which does test compressions
    * of lines using different filter methods, and then chooses the
    * (series of) filter(s) that give minimum compressed data size (VERY
    * computationally expensive).
    *
    * GRR 980525:  consider also
    *
    *   (1) minimum sum of absolute differences from running average (i.e.,
    *       keep running sum of non-absolute differences & count of bytes)
    *       [track dispersion, too?  restart average if dispersion too large?]
    *
    *  (1b) minimum sum of absolute differences from sliding average, probably
    *       with window size <= deflate window (usually 32K)
    *
    *   (2) minimum sum of squared differences from zero or running average
    *       (i.e., ~ root-mean-square approach)
    */


   /* We don't need to test the 'no filter' case if this is the only filter
    * that has been chosen, as it doesn't actually do anything to the data.
    */
   best_row = png_ptr->row_buf;

   if (PNG_SIZE_MAX/128 <= row_bytes)
   {
      /* Overflow can occur in the calculation, just select the lowest set
       * filter.
       */
      filter_to_do &= 0U-filter_to_do;
   }
   else if ((filter_to_do & PNG_FILTER_NONE) != 0 &&
         filter_to_do != PNG_FILTER_NONE)
   {
      /* Overflow not possible and multiple filters in the list, including the
       * 'none' filter.
       */
      png_bytep rp;
      size_t sum = 0;
      size_t i;
      unsigned int v;

      {
         for (i = 0, rp = row_buf + 1; i < row_bytes; i++, rp++)
         {
            v = *rp;
#ifdef PNG_USE_ABS
            sum += 128 - abs((int)v - 128);
#else
            sum += (v < 128) ? v : 256 - v;
#endif
         }
      }

      mins = sum;
   }

   /* Sub filter */
   if (filter_to_do == PNG_FILTER_SUB)
   /* It's the only filter so no testing is needed */
   {
      png_setup_sub_row_only(png_ptr, bpp, row_bytes);
      best_row = png_ptr->try_row;
   }

   else if ((filter_to_do & PNG_FILTER_SUB) != 0)
   {
      size_t sum;
      size_t lmins = mins;

      sum = png_setup_sub_row(png_ptr, bpp, row_bytes, lmins);

      if (sum < mins)
      {
         mins = sum;
         best_row = png_ptr->try_row;
         if (png_ptr->tst_row != NULL)
         {
            png_ptr->try_row = png_ptr->tst_row;
            png_ptr->tst_row = best_row;
         }
      }
   }

   /* Up filter */
   if (filter_to_do == PNG_FILTER_UP)
   {
      png_setup_up_row_only(png_ptr, row_bytes);
      best_row = png_ptr->try_row;
   }

   else if ((filter_to_do & PNG_FILTER_UP) != 0)
   {
      size_t sum;
      size_t lmins = mins;

      sum = png_setup_up_row(png_ptr, row_bytes, lmins);

      if (sum < mins)
      {
         mins = sum;
         best_row = png_ptr->try_row;
         if (png_ptr->tst_row != NULL)
         {
            png_ptr->try_row = png_ptr->tst_row;
            png_ptr->tst_row = best_row;
         }
      }
   }

   /* Avg filter */
   if (filter_to_do == PNG_FILTER_AVG)
   {
      png_setup_avg_row_only(png_ptr, bpp, row_bytes);
      best_row = png_ptr->try_row;
   }

   else if ((filter_to_do & PNG_FILTER_AVG) != 0)
   {
      size_t sum;
      size_t lmins = mins;

      sum= png_setup_avg_row(png_ptr, bpp, row_bytes, lmins);

      if (sum < mins)
      {
         mins = sum;
         best_row = png_ptr->try_row;
         if (png_ptr->tst_row != NULL)
         {
            png_ptr->try_row = png_ptr->tst_row;
            png_ptr->tst_row = best_row;
         }
      }
   }

   /* Paeth filter */
   if (filter_to_do == PNG_FILTER_PAETH)
   {
      png_setup_paeth_row_only(png_ptr, bpp, row_bytes);
      best_row = png_ptr->try_row;
   }

   else if ((filter_to_do & PNG_FILTER_PAETH) != 0)
   {
      size_t sum;
      size_t lmins = mins;

      sum = png_setup_paeth_row(png_ptr, bpp, row_bytes, lmins);

      if (sum < mins)
      {
         best_row = png_ptr->try_row;
         if (png_ptr->tst_row != NULL)
         {
            png_ptr->try_row = png_ptr->tst_row;
            png_ptr->tst_row = best_row;
         }
      }
   }

   /* Do the actual writing of the filtered row data from the chosen filter. */
   png_write_filtered_row(png_ptr, best_row, row_info->rowbytes+1);

#endif /* WRITE_FILTER */
}