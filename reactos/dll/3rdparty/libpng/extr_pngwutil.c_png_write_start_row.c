#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  int png_byte ;
typedef  scalar_t__ png_alloc_size_t ;
struct TYPE_5__ {int usr_channels; int usr_bit_depth; int width; int maximum_pixel_depth; int do_filter; int height; scalar_t__ interlaced; int transformations; int num_rows; int usr_width; void* prev_row; void* tst_row; int /*<<< orphan*/ * try_row; int /*<<< orphan*/ * row_buf; int /*<<< orphan*/  pixel_depth; int /*<<< orphan*/  transformed_pixel_depth; } ;

/* Variables and functions */
 int PNG_FILTER_AVG ; 
 int PNG_FILTER_NONE ; 
 int PNG_FILTER_PAETH ; 
 int PNG_FILTER_SUB ; 
 int PNG_FILTER_UP ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_NONE ; 
 int PNG_INTERLACE ; 
 scalar_t__ PNG_ROWBYTES (int,int) ; 
 int /*<<< orphan*/  png_bytep ; 
 int /*<<< orphan*/  png_calloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_malloc (TYPE_1__*,scalar_t__) ; 
 void* png_voidcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_start_row(png_structrp png_ptr)
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

   png_alloc_size_t buf_size;
   int usr_pixel_depth;

#ifdef PNG_WRITE_FILTER_SUPPORTED
   png_byte filters;
#endif

   png_debug(1, "in png_write_start_row");

   usr_pixel_depth = png_ptr->usr_channels * png_ptr->usr_bit_depth;
   buf_size = PNG_ROWBYTES(usr_pixel_depth, png_ptr->width) + 1;

   /* 1.5.6: added to allow checking in the row write code. */
   png_ptr->transformed_pixel_depth = png_ptr->pixel_depth;
   png_ptr->maximum_pixel_depth = (png_byte)usr_pixel_depth;

   /* Set up row buffer */
   png_ptr->row_buf = png_voidcast(png_bytep, png_malloc(png_ptr, buf_size));

   png_ptr->row_buf[0] = PNG_FILTER_VALUE_NONE;

#ifdef PNG_WRITE_FILTER_SUPPORTED
   filters = png_ptr->do_filter;

   if (png_ptr->height == 1)
      filters &= 0xff & ~(PNG_FILTER_UP|PNG_FILTER_AVG|PNG_FILTER_PAETH);

   if (png_ptr->width == 1)
      filters &= 0xff & ~(PNG_FILTER_SUB|PNG_FILTER_AVG|PNG_FILTER_PAETH);

   if (filters == 0)
      filters = PNG_FILTER_NONE;

   png_ptr->do_filter = filters;

   if (((filters & (PNG_FILTER_SUB | PNG_FILTER_UP | PNG_FILTER_AVG |
       PNG_FILTER_PAETH)) != 0) && png_ptr->try_row == NULL)
   {
      int num_filters = 0;

      png_ptr->try_row = png_voidcast(png_bytep, png_malloc(png_ptr, buf_size));

      if (filters & PNG_FILTER_SUB)
         num_filters++;

      if (filters & PNG_FILTER_UP)
         num_filters++;

      if (filters & PNG_FILTER_AVG)
         num_filters++;

      if (filters & PNG_FILTER_PAETH)
         num_filters++;

      if (num_filters > 1)
         png_ptr->tst_row = png_voidcast(png_bytep, png_malloc(png_ptr,
             buf_size));
   }

   /* We only need to keep the previous row if we are using one of the following
    * filters.
    */
   if ((filters & (PNG_FILTER_AVG | PNG_FILTER_UP | PNG_FILTER_PAETH)) != 0)
      png_ptr->prev_row = png_voidcast(png_bytep,
          png_calloc(png_ptr, buf_size));
#endif /* WRITE_FILTER */

#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   /* If interlaced, we need to set up width and height of pass */
   if (png_ptr->interlaced != 0)
   {
      if ((png_ptr->transformations & PNG_INTERLACE) == 0)
      {
         png_ptr->num_rows = (png_ptr->height + png_pass_yinc[0] - 1 -
             png_pass_ystart[0]) / png_pass_yinc[0];

         png_ptr->usr_width = (png_ptr->width + png_pass_inc[0] - 1 -
             png_pass_start[0]) / png_pass_inc[0];
      }

      else
      {
         png_ptr->num_rows = png_ptr->height;
         png_ptr->usr_width = png_ptr->width;
      }
   }

   else
#endif
   {
      png_ptr->num_rows = png_ptr->height;
      png_ptr->usr_width = png_ptr->width;
   }
}