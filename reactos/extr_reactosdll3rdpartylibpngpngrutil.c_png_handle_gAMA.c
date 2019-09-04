#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_9__ {int mode; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_colorspace_set_gamma (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_colorspace_sync (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_get_fixed_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void /* PRIVATE */
png_handle_gAMA(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_fixed_point igamma;
   png_byte buf[4];

   png_debug(1, "in png_handle_gAMA");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   else if ((png_ptr->mode & (PNG_HAVE_IDAT|PNG_HAVE_PLTE)) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
   }

   if (length != 4)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
   }

   png_crc_read(png_ptr, buf, 4);

   if (png_crc_finish(png_ptr, 0) != 0)
      return;

   igamma = png_get_fixed_point(NULL, buf);

   png_colorspace_set_gamma(png_ptr, &png_ptr->colorspace, igamma);
   png_colorspace_sync(png_ptr, info_ptr);
}