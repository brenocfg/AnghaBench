#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
typedef  TYPE_1__* png_structp ;
typedef  scalar_t__ png_size_t ;
struct TYPE_8__ {scalar_t__ avail_out; char* msg; int /*<<< orphan*/  data_type; int /*<<< orphan*/  next_out; } ;
struct TYPE_7__ {int row_number; int num_rows; int transformations; int pass; int usr_width; int width; int height; int usr_channels; int usr_bit_depth; scalar_t__ zbuf_size; TYPE_5__ zstream; int /*<<< orphan*/  zbuf; int /*<<< orphan*/ * prev_row; scalar_t__ interlaced; } ;

/* Variables and functions */
 int PNG_INTERLACE ; 
 scalar_t__ PNG_ROWBYTES (int,int) ; 
 int /*<<< orphan*/  Z_BINARY ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateReset (TYPE_5__*) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_write_IDAT (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_write_finish_row(png_structp png_ptr)
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

   int ret;

   png_debug(1, "in png_write_finish_row\n");
   /* next row */
   png_ptr->row_number++;

   /* see if we are done */
   if (png_ptr->row_number < png_ptr->num_rows)
      return;

#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   /* if interlaced, go to next pass */
   if (png_ptr->interlaced)
   {
      png_ptr->row_number = 0;
      if (png_ptr->transformations & PNG_INTERLACE)
      {
         png_ptr->pass++;
      }
      else
      {
         /* loop until we find a non-zero width or height pass */
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
            if (png_ptr->transformations & PNG_INTERLACE)
               break;
         } while (png_ptr->usr_width == 0 || png_ptr->num_rows == 0);

      }

      /* reset the row above the image for the next pass */
      if (png_ptr->pass < 7)
      {
         if (png_ptr->prev_row != NULL)
            png_memset(png_ptr->prev_row, 0,
               (png_size_t)(PNG_ROWBYTES(png_ptr->usr_channels*
               png_ptr->usr_bit_depth,png_ptr->width))+1);
         return;
      }
   }
#endif

   /* if we get here, we've just written the last row, so we need
      to flush the compressor */
   do
   {
      /* tell the compressor we are done */
      ret = deflate(&png_ptr->zstream, Z_FINISH);
      /* check for an error */
      if (ret == Z_OK)
      {
         /* check to see if we need more room */
         if (!(png_ptr->zstream.avail_out))
         {
            png_write_IDAT(png_ptr, png_ptr->zbuf, png_ptr->zbuf_size);
            png_ptr->zstream.next_out = png_ptr->zbuf;
            png_ptr->zstream.avail_out = (uInt)png_ptr->zbuf_size;
         }
      }
      else if (ret != Z_STREAM_END)
      {
         if (png_ptr->zstream.msg != NULL)
            png_error(png_ptr, png_ptr->zstream.msg);
         else
            png_error(png_ptr, "zlib error");
      }
   } while (ret != Z_STREAM_END);

   /* write any extra space */
   if (png_ptr->zstream.avail_out < png_ptr->zbuf_size)
   {
      png_write_IDAT(png_ptr, png_ptr->zbuf, png_ptr->zbuf_size -
         png_ptr->zstream.avail_out);
   }

   deflateReset(&png_ptr->zstream);
   png_ptr->zstream.data_type = Z_BINARY;
}