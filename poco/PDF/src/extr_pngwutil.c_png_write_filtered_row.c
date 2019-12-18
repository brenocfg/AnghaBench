#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uInt ;
typedef  TYPE_2__* png_structp ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_11__ {char* msg; void* avail_out; int /*<<< orphan*/  next_out; void* avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_9__ {scalar_t__ rowbytes; } ;
struct TYPE_10__ {scalar_t__ flush_rows; scalar_t__ flush_dist; int /*<<< orphan*/ * row_buf; int /*<<< orphan*/ * prev_row; scalar_t__ zbuf_size; TYPE_8__ zstream; int /*<<< orphan*/  zbuf; TYPE_1__ row_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int deflate (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_write_IDAT (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_write_finish_row (TYPE_2__*) ; 
 int /*<<< orphan*/  png_write_flush (TYPE_2__*) ; 

void /* PRIVATE */
png_write_filtered_row(png_structp png_ptr, png_bytep filtered_row)
{
   png_debug(1, "in png_write_filtered_row\n");
   png_debug1(2, "filter = %d\n", filtered_row[0]);
   /* set up the zlib input buffer */

   png_ptr->zstream.next_in = filtered_row;
   png_ptr->zstream.avail_in = (uInt)png_ptr->row_info.rowbytes + 1;
   /* repeat until we have compressed all the data */
   do
   {
      int ret; /* return of zlib */

      /* compress the data */
      ret = deflate(&png_ptr->zstream, Z_NO_FLUSH);
      /* check for compression errors */
      if (ret != Z_OK)
      {
         if (png_ptr->zstream.msg != NULL)
            png_error(png_ptr, png_ptr->zstream.msg);
         else
            png_error(png_ptr, "zlib error");
      }

      /* see if it is time to write another IDAT */
      if (!(png_ptr->zstream.avail_out))
      {
         /* write the IDAT and reset the zlib output buffer */
         png_write_IDAT(png_ptr, png_ptr->zbuf, png_ptr->zbuf_size);
         png_ptr->zstream.next_out = png_ptr->zbuf;
         png_ptr->zstream.avail_out = (uInt)png_ptr->zbuf_size;
      }
   /* repeat until all data has been compressed */
   } while (png_ptr->zstream.avail_in);

   /* swap the current and previous rows */
   if (png_ptr->prev_row != NULL)
   {
      png_bytep tptr;

      tptr = png_ptr->prev_row;
      png_ptr->prev_row = png_ptr->row_buf;
      png_ptr->row_buf = tptr;
   }

   /* finish row - updates counters and flushes zlib if last row */
   png_write_finish_row(png_ptr);

#if defined(PNG_WRITE_FLUSH_SUPPORTED)
   png_ptr->flush_rows++;

   if (png_ptr->flush_dist > 0 &&
       png_ptr->flush_rows >= png_ptr->flush_dist)
   {
      png_write_flush(png_ptr);
   }
#endif
}