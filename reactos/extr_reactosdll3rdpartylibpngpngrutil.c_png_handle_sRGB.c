#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int mode; TYPE_7__ colorspace; } ;

/* Variables and functions */
 int PNG_COLORSPACE_HAVE_INTENT ; 
 int PNG_COLORSPACE_INVALID ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_colorspace_set_sRGB (TYPE_1__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_colorspace_sync (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_handle_sRGB(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte intent;

   png_debug(1, "in png_handle_sRGB");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   else if ((png_ptr->mode & (PNG_HAVE_IDAT|PNG_HAVE_PLTE)) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
   }

   if (length != 1)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
   }

   png_crc_read(png_ptr, &intent, 1);

   if (png_crc_finish(png_ptr, 0) != 0)
      return;

   /* If a colorspace error has already been output skip this chunk */
   if ((png_ptr->colorspace.flags & PNG_COLORSPACE_INVALID) != 0)
      return;

   /* Only one sRGB or iCCP chunk is allowed, use the HAVE_INTENT flag to detect
    * this.
    */
   if ((png_ptr->colorspace.flags & PNG_COLORSPACE_HAVE_INTENT) != 0)
   {
      png_ptr->colorspace.flags |= PNG_COLORSPACE_INVALID;
      png_colorspace_sync(png_ptr, info_ptr);
      png_chunk_benign_error(png_ptr, "too many profiles");
      return;
   }

   (void)png_colorspace_set_sRGB(png_ptr, &png_ptr->colorspace, intent);
   png_colorspace_sync(png_ptr, info_ptr);
}