#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_6__ {scalar_t__ flush_rows; scalar_t__ flush_dist; int /*<<< orphan*/ * row_buf; int /*<<< orphan*/ * prev_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  png_compress_IDAT (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_finish_row (TYPE_1__*) ; 
 int /*<<< orphan*/  png_write_flush (TYPE_1__*) ; 

__attribute__((used)) static void
png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row,
    size_t full_row_length/*includes filter byte*/)
{
   png_debug(1, "in png_write_filtered_row");

   png_debug1(2, "filter = %d", filtered_row[0]);

   png_compress_IDAT(png_ptr, filtered_row, full_row_length, Z_NO_FLUSH);

#ifdef PNG_WRITE_FILTER_SUPPORTED
   /* Swap the current and previous rows */
   if (png_ptr->prev_row != NULL)
   {
      png_bytep tptr;

      tptr = png_ptr->prev_row;
      png_ptr->prev_row = png_ptr->row_buf;
      png_ptr->row_buf = tptr;
   }
#endif /* WRITE_FILTER */

   /* Finish row - updates counters and flushes zlib if last row */
   png_write_finish_row(png_ptr);

#ifdef PNG_WRITE_FLUSH_SUPPORTED
   png_ptr->flush_rows++;

   if (png_ptr->flush_dist > 0 &&
       png_ptr->flush_rows >= png_ptr->flush_dist)
   {
      png_write_flush(png_ptr);
   }
#endif /* WRITE_FLUSH */
}