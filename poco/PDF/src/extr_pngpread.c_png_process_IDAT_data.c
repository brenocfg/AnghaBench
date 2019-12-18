#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uInt ;
typedef  TYPE_1__* png_structp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/  png_bytep ;
struct TYPE_8__ {int /*<<< orphan*/  next_out; void* avail_out; void* avail_in; int /*<<< orphan*/  next_in; } ;
struct TYPE_7__ {int flags; int pass; scalar_t__ row_number; scalar_t__ num_rows; int /*<<< orphan*/  row_buf; TYPE_6__ zstream; scalar_t__ irowbytes; scalar_t__ interlaced; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_AFTER_IDAT ; 
 int PNG_FLAG_ZLIB_FINISHED ; 
 int Z_BUF_ERROR ; 
 int Z_OK ; 
 int /*<<< orphan*/  Z_PARTIAL_FLUSH ; 
 int Z_STREAM_END ; 
 int inflate (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_push_process_row (TYPE_1__*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_process_IDAT_data(png_structp png_ptr, png_bytep buffer,
   png_size_t buffer_length)
{
   int ret;

   if ((png_ptr->flags & PNG_FLAG_ZLIB_FINISHED) && buffer_length)
      png_error(png_ptr, "Extra compression data");

   png_ptr->zstream.next_in = buffer;
   png_ptr->zstream.avail_in = (uInt)buffer_length;
   for(;;)
   {
      ret = inflate(&png_ptr->zstream, Z_PARTIAL_FLUSH);
      if (ret != Z_OK)
      {
         if (ret == Z_STREAM_END)
         {
            if (png_ptr->zstream.avail_in)
               png_error(png_ptr, "Extra compressed data");
            if (!(png_ptr->zstream.avail_out))
            {
               png_push_process_row(png_ptr);
            }

            png_ptr->mode |= PNG_AFTER_IDAT;
            png_ptr->flags |= PNG_FLAG_ZLIB_FINISHED;
            break;
         }
         else if (ret == Z_BUF_ERROR)
            break;
         else
            png_error(png_ptr, "Decompression Error");
      }
      if (!(png_ptr->zstream.avail_out))
      {
         if ((
#if defined(PNG_READ_INTERLACING_SUPPORTED)
             png_ptr->interlaced && png_ptr->pass > 6) ||
             (!png_ptr->interlaced &&
#endif
             png_ptr->row_number == png_ptr->num_rows))
         {
           if (png_ptr->zstream.avail_in)
             png_warning(png_ptr, "Too much data in IDAT chunks");
           png_ptr->flags |= PNG_FLAG_ZLIB_FINISHED;
           break;
         }
         png_push_process_row(png_ptr);
         png_ptr->zstream.avail_out = (uInt)png_ptr->irowbytes;
         png_ptr->zstream.next_out = png_ptr->row_buf;
      }
      else
         break;
   }
}