#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_2__* png_structp ;
typedef  scalar_t__ png_size_t ;
typedef  void* png_bytep ;
struct TYPE_5__ {int /*<<< orphan*/  next_out; scalar_t__ avail_out; } ;
struct TYPE_6__ {int usr_channels; int usr_bit_depth; int width; int do_filter; int transformations; int num_rows; int height; int usr_width; int /*<<< orphan*/  zbuf; TYPE_1__ zstream; scalar_t__ zbuf_size; scalar_t__ interlaced; int /*<<< orphan*/ * paeth_row; scalar_t__ rowbytes; int /*<<< orphan*/ * avg_row; int /*<<< orphan*/ * up_row; void* prev_row; int /*<<< orphan*/ * sub_row; int /*<<< orphan*/ * row_buf; } ;

/* Variables and functions */
 int PNG_FILTER_AVG ; 
 int PNG_FILTER_PAETH ; 
 int PNG_FILTER_SUB ; 
 int PNG_FILTER_UP ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_AVG ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_NONE ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_PAETH ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_SUB ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_UP ; 
 int PNG_INTERLACE ; 
 scalar_t__ PNG_ROWBYTES (int,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 scalar_t__ png_malloc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  png_memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_write_start_row(png_structp png_ptr)
{
#ifdef PNG_WRITE_INTERLACING_SUPPORTED
#ifdef PNG_USE_LOCAL_ARRAYS
   /* arrays to facilitate easy interlacing - use pass (0 - 6) as index */

   /* start of interlace block */
   int png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};

   /* offset to next interlace block */
   int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};

   /* start of interlace block in the y direction */
   int png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};

   /* offset to next interlace block in the y direction */
   int png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
#endif
#endif

   png_size_t buf_size;

   png_debug(1, "in png_write_start_row\n");
   buf_size = (png_size_t)(PNG_ROWBYTES(
      png_ptr->usr_channels*png_ptr->usr_bit_depth,png_ptr->width)+1);

   /* set up row buffer */
   png_ptr->row_buf = (png_bytep)png_malloc(png_ptr, (png_uint_32)buf_size);
   png_ptr->row_buf[0] = PNG_FILTER_VALUE_NONE;

#ifndef PNG_NO_WRITE_FILTERING
   /* set up filtering buffer, if using this filter */
   if (png_ptr->do_filter & PNG_FILTER_SUB)
   {
      png_ptr->sub_row = (png_bytep)png_malloc(png_ptr,
         (png_ptr->rowbytes + 1));
      png_ptr->sub_row[0] = PNG_FILTER_VALUE_SUB;
   }

   /* We only need to keep the previous row if we are using one of these. */
   if (png_ptr->do_filter & (PNG_FILTER_AVG | PNG_FILTER_UP | PNG_FILTER_PAETH))
   {
     /* set up previous row buffer */
      png_ptr->prev_row = (png_bytep)png_malloc(png_ptr, (png_uint_32)buf_size);
      png_memset(png_ptr->prev_row, 0, buf_size);

      if (png_ptr->do_filter & PNG_FILTER_UP)
      {
         png_ptr->up_row = (png_bytep)png_malloc(png_ptr,
            (png_ptr->rowbytes + 1));
         png_ptr->up_row[0] = PNG_FILTER_VALUE_UP;
      }

      if (png_ptr->do_filter & PNG_FILTER_AVG)
      {
         png_ptr->avg_row = (png_bytep)png_malloc(png_ptr,
            (png_ptr->rowbytes + 1));
         png_ptr->avg_row[0] = PNG_FILTER_VALUE_AVG;
      }

      if (png_ptr->do_filter & PNG_FILTER_PAETH)
      {
         png_ptr->paeth_row = (png_bytep)png_malloc(png_ptr,
            (png_ptr->rowbytes + 1));
         png_ptr->paeth_row[0] = PNG_FILTER_VALUE_PAETH;
      }
#endif /* PNG_NO_WRITE_FILTERING */
   }

#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   /* if interlaced, we need to set up width and height of pass */
   if (png_ptr->interlaced)
   {
      if (!(png_ptr->transformations & PNG_INTERLACE))
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
   png_ptr->zstream.avail_out = (uInt)png_ptr->zbuf_size;
   png_ptr->zstream.next_out = png_ptr->zbuf;
}