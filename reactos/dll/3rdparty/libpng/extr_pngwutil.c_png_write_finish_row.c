#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  int png_byte ;
struct TYPE_4__ {int row_number; int num_rows; scalar_t__ interlaced; int transformations; int pass; int usr_width; int const width; int const height; int usr_channels; int usr_bit_depth; int /*<<< orphan*/ * prev_row; } ;

/* Variables and functions */
 int PNG_INTERLACE ; 
 scalar_t__ PNG_ROWBYTES (int,int const) ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_compress_IDAT (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_write_finish_row(png_structrp png_ptr)
{
#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   /* Arrays to facilitate easy interlacing - use pass (0 - 6) as index */

   /* Start of interlace block */
   static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};

   /* Offset to next interlace block */
   static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};

   /* Start of interlace block in the y direction */
   static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};

   /* Offset to next interlace block in the y direction */
   static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
#endif

   png_debug(1, "in png_write_finish_row");

   /* Next row */
   png_ptr->row_number++;

   /* See if we are done */
   if (png_ptr->row_number < png_ptr->num_rows)
      return;

#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   /* If interlaced, go to next pass */
   if (png_ptr->interlaced != 0)
   {
      png_ptr->row_number = 0;
      if ((png_ptr->transformations & PNG_INTERLACE) != 0)
      {
         png_ptr->pass++;
      }

      else
      {
         /* Loop until we find a non-zero width or height pass */
         do
         {
            png_ptr->pass++;

            if (png_ptr->pass >= 7)
               break;

            png_ptr->usr_width = (png_ptr->width +
                png_pass_inc[png_ptr->pass] - 1 -
                png_pass_start[png_ptr->pass]) /
                png_pass_inc[png_ptr->pass];

            png_ptr->num_rows = (png_ptr->height +
                png_pass_yinc[png_ptr->pass] - 1 -
                png_pass_ystart[png_ptr->pass]) /
                png_pass_yinc[png_ptr->pass];

            if ((png_ptr->transformations & PNG_INTERLACE) != 0)
               break;

         } while (png_ptr->usr_width == 0 || png_ptr->num_rows == 0);

      }

      /* Reset the row above the image for the next pass */
      if (png_ptr->pass < 7)
      {
         if (png_ptr->prev_row != NULL)
            memset(png_ptr->prev_row, 0,
                PNG_ROWBYTES(png_ptr->usr_channels *
                png_ptr->usr_bit_depth, png_ptr->width) + 1);

         return;
      }
   }
#endif

   /* If we get here, we've just written the last row, so we need
      to flush the compressor */
   png_compress_IDAT(png_ptr, NULL, 0, Z_FINISH);
}