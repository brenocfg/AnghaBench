#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
struct TYPE_11__ {int /*<<< orphan*/  width; int /*<<< orphan*/  pixel_depth; int /*<<< orphan*/  rowbytes; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  channels; int /*<<< orphan*/  color_type; } ;
struct TYPE_10__ {int transformations; int flags; int pass; int height; scalar_t__* row_buf; scalar_t__ interlaced; scalar_t__ rowbytes; scalar_t__ prev_row; TYPE_4__ row_info; int /*<<< orphan*/  pixel_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  channels; int /*<<< orphan*/  iwidth; int /*<<< orphan*/  color_type; } ;

/* Variables and functions */
 int PNG_FLAG_STRIP_ALPHA ; 
 int PNG_INTERLACE ; 
 int /*<<< orphan*/  PNG_ROWBYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* png_bytep_NULL ; 
 int /*<<< orphan*/  png_do_read_interlace (TYPE_1__*) ; 
 int /*<<< orphan*/  png_do_read_transformations (TYPE_1__*) ; 
 int /*<<< orphan*/  png_memcpy_check (TYPE_1__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  png_push_have_row (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  png_read_filter_row (TYPE_1__*,TYPE_4__*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  png_read_push_finish_row (TYPE_1__*) ; 

void /* PRIVATE */
png_push_process_row(png_structp png_ptr)
{
   png_ptr->row_info.color_type = png_ptr->color_type;
   png_ptr->row_info.width = png_ptr->iwidth;
   png_ptr->row_info.channels = png_ptr->channels;
   png_ptr->row_info.bit_depth = png_ptr->bit_depth;
   png_ptr->row_info.pixel_depth = png_ptr->pixel_depth;

   png_ptr->row_info.rowbytes = PNG_ROWBYTES(png_ptr->row_info.pixel_depth,
       png_ptr->row_info.width);

   png_read_filter_row(png_ptr, &(png_ptr->row_info),
      png_ptr->row_buf + 1, png_ptr->prev_row + 1,
      (int)(png_ptr->row_buf[0]));

   png_memcpy_check(png_ptr, png_ptr->prev_row, png_ptr->row_buf,
      png_ptr->rowbytes + 1);

   if (png_ptr->transformations || (png_ptr->flags&PNG_FLAG_STRIP_ALPHA))
      png_do_read_transformations(png_ptr);

#if defined(PNG_READ_INTERLACING_SUPPORTED)
   /* blow up interlaced rows to full size */
   if (png_ptr->interlaced && (png_ptr->transformations & PNG_INTERLACE))
   {
      if (png_ptr->pass < 6)
/*       old interface (pre-1.0.9):
         png_do_read_interlace(&(png_ptr->row_info),
            png_ptr->row_buf + 1, png_ptr->pass, png_ptr->transformations);
 */
         png_do_read_interlace(png_ptr);

    switch (png_ptr->pass)
    {
         case 0:
         {
            int i;
            for (i = 0; i < 8 && png_ptr->pass == 0; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr); /* updates png_ptr->pass */
            }
            if (png_ptr->pass == 2) /* pass 1 might be empty */
            {
               for (i = 0; i < 4 && png_ptr->pass == 2; i++)
               {
                  png_push_have_row(png_ptr, png_bytep_NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }
            if (png_ptr->pass == 4 && png_ptr->height <= 4)
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, png_bytep_NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }
            if (png_ptr->pass == 6 && png_ptr->height <= 4)
            {
                png_push_have_row(png_ptr, png_bytep_NULL);
                png_read_push_finish_row(png_ptr);
            }
            break;
         }
         case 1:
         {
            int i;
            for (i = 0; i < 8 && png_ptr->pass == 1; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }
            if (png_ptr->pass == 2) /* skip top 4 generated rows */
            {
               for (i = 0; i < 4 && png_ptr->pass == 2; i++)
               {
                  png_push_have_row(png_ptr, png_bytep_NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }
            break;
         }
         case 2:
         {
            int i;
            for (i = 0; i < 4 && png_ptr->pass == 2; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }
            for (i = 0; i < 4 && png_ptr->pass == 2; i++)
            {
               png_push_have_row(png_ptr, png_bytep_NULL);
               png_read_push_finish_row(png_ptr);
            }
            if (png_ptr->pass == 4) /* pass 3 might be empty */
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, png_bytep_NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }
            break;
         }
         case 3:
         {
            int i;
            for (i = 0; i < 4 && png_ptr->pass == 3; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }
            if (png_ptr->pass == 4) /* skip top two generated rows */
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, png_bytep_NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }
            break;
         }
         case 4:
         {
            int i;
            for (i = 0; i < 2 && png_ptr->pass == 4; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }
            for (i = 0; i < 2 && png_ptr->pass == 4; i++)
            {
               png_push_have_row(png_ptr, png_bytep_NULL);
               png_read_push_finish_row(png_ptr);
            }
            if (png_ptr->pass == 6) /* pass 5 might be empty */
            {
               png_push_have_row(png_ptr, png_bytep_NULL);
               png_read_push_finish_row(png_ptr);
            }
            break;
         }
         case 5:
         {
            int i;
            for (i = 0; i < 2 && png_ptr->pass == 5; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }
            if (png_ptr->pass == 6) /* skip top generated row */
            {
               png_push_have_row(png_ptr, png_bytep_NULL);
               png_read_push_finish_row(png_ptr);
            }
            break;
         }
         case 6:
         {
            png_push_have_row(png_ptr, png_ptr->row_buf + 1);
            png_read_push_finish_row(png_ptr);
            if (png_ptr->pass != 6)
               break;
            png_push_have_row(png_ptr, png_bytep_NULL);
            png_read_push_finish_row(png_ptr);
         }
      }
   }
   else
#endif
   {
      png_push_have_row(png_ptr, png_ptr->row_buf + 1);
      png_read_push_finish_row(png_ptr);
   }
}