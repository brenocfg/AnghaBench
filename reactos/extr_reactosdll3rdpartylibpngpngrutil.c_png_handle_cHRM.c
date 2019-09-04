#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ whitex; scalar_t__ whitey; scalar_t__ redx; scalar_t__ redy; scalar_t__ greenx; scalar_t__ greeny; scalar_t__ bluex; scalar_t__ bluey; } ;
typedef  TYPE_1__ png_xy ;
typedef  int png_uint_32 ;
typedef  TYPE_2__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int mode; TYPE_8__ colorspace; } ;

/* Variables and functions */
 int PNG_COLORSPACE_FROM_cHRM ; 
 int PNG_COLORSPACE_INVALID ; 
 scalar_t__ PNG_FIXED_ERROR ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_colorspace_set_chromaticities (TYPE_2__*,TYPE_8__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_colorspace_sync (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_crc_finish (TYPE_2__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 void* png_get_fixed_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void /* PRIVATE */
png_handle_cHRM(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte buf[32];
   png_xy xy;

   png_debug(1, "in png_handle_cHRM");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   else if ((png_ptr->mode & (PNG_HAVE_IDAT|PNG_HAVE_PLTE)) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
   }

   if (length != 32)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
   }

   png_crc_read(png_ptr, buf, 32);

   if (png_crc_finish(png_ptr, 0) != 0)
      return;

   xy.whitex = png_get_fixed_point(NULL, buf);
   xy.whitey = png_get_fixed_point(NULL, buf + 4);
   xy.redx   = png_get_fixed_point(NULL, buf + 8);
   xy.redy   = png_get_fixed_point(NULL, buf + 12);
   xy.greenx = png_get_fixed_point(NULL, buf + 16);
   xy.greeny = png_get_fixed_point(NULL, buf + 20);
   xy.bluex  = png_get_fixed_point(NULL, buf + 24);
   xy.bluey  = png_get_fixed_point(NULL, buf + 28);

   if (xy.whitex == PNG_FIXED_ERROR ||
       xy.whitey == PNG_FIXED_ERROR ||
       xy.redx   == PNG_FIXED_ERROR ||
       xy.redy   == PNG_FIXED_ERROR ||
       xy.greenx == PNG_FIXED_ERROR ||
       xy.greeny == PNG_FIXED_ERROR ||
       xy.bluex  == PNG_FIXED_ERROR ||
       xy.bluey  == PNG_FIXED_ERROR)
   {
      png_chunk_benign_error(png_ptr, "invalid values");
      return;
   }

   /* If a colorspace error has already been output skip this chunk */
   if ((png_ptr->colorspace.flags & PNG_COLORSPACE_INVALID) != 0)
      return;

   if ((png_ptr->colorspace.flags & PNG_COLORSPACE_FROM_cHRM) != 0)
   {
      png_ptr->colorspace.flags |= PNG_COLORSPACE_INVALID;
      png_colorspace_sync(png_ptr, info_ptr);
      png_chunk_benign_error(png_ptr, "duplicate");
      return;
   }

   png_ptr->colorspace.flags |= PNG_COLORSPACE_FROM_cHRM;
   (void)png_colorspace_set_chromaticities(png_ptr, &png_ptr->colorspace, &xy,
       1/*prefer cHRM values*/);
   png_colorspace_sync(png_ptr, info_ptr);
}