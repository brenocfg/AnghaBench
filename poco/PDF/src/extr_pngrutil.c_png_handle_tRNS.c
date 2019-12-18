#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int png_uint_16 ;
typedef  TYPE_1__* png_structp ;
typedef  int png_size_t ;
typedef  TYPE_2__* png_infop ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_14__ {int gray; int red; int green; int blue; } ;
struct TYPE_13__ {int valid; } ;
struct TYPE_12__ {int bit_depth; int mode; scalar_t__ color_type; int num_trans; TYPE_6__ trans_values; scalar_t__ num_palette; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_GRAY ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 scalar_t__ PNG_COLOR_TYPE_RGB ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_INFO_tRNS ; 
 int PNG_MAX_PALETTE_LENGTH ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int png_get_uint_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_tRNS (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_handle_tRNS(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   png_byte readbuf[PNG_MAX_PALETTE_LENGTH];
   int bit_mask;

   png_debug(1, "in png_handle_tRNS\n");

   /* For non-indexed color, mask off any bits in the tRNS value that
    * exceed the bit depth.  Some creators were writing extra bits there.
    * This is not needed for indexed color. */
   bit_mask = (1 << png_ptr->bit_depth) - 1;

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before tRNS");
   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid tRNS after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }
   else if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_tRNS))
   {
      png_warning(png_ptr, "Duplicate tRNS chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (png_ptr->color_type == PNG_COLOR_TYPE_GRAY)
   {
      png_byte buf[2];

      if (length != 2)
      {
         png_warning(png_ptr, "Incorrect tRNS chunk length");
         png_crc_finish(png_ptr, length);
         return;
      }

      png_crc_read(png_ptr, buf, 2);
      png_ptr->num_trans = 1;
      png_ptr->trans_values.gray = png_get_uint_16(buf) & bit_mask;
   }
   else if (png_ptr->color_type == PNG_COLOR_TYPE_RGB)
   {
      png_byte buf[6];

      if (length != 6)
      {
         png_warning(png_ptr, "Incorrect tRNS chunk length");
         png_crc_finish(png_ptr, length);
         return;
      }
      png_crc_read(png_ptr, buf, (png_size_t)length);
      png_ptr->num_trans = 1;
      png_ptr->trans_values.red = png_get_uint_16(buf) & bit_mask;
      png_ptr->trans_values.green = png_get_uint_16(buf + 2) & bit_mask;
      png_ptr->trans_values.blue = png_get_uint_16(buf + 4) & bit_mask;
   }
   else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (!(png_ptr->mode & PNG_HAVE_PLTE))
      {
         /* Should be an error, but we can cope with it. */
         png_warning(png_ptr, "Missing PLTE before tRNS");
      }
      if (length > (png_uint_32)png_ptr->num_palette ||
          length > PNG_MAX_PALETTE_LENGTH)
      {
         png_warning(png_ptr, "Incorrect tRNS chunk length");
         png_crc_finish(png_ptr, length);
         return;
      }
      if (length == 0)
      {
         png_warning(png_ptr, "Zero length tRNS chunk");
         png_crc_finish(png_ptr, length);
         return;
      }
      png_crc_read(png_ptr, readbuf, (png_size_t)length);
      png_ptr->num_trans = (png_uint_16)length;
   }
   else
   {
      png_warning(png_ptr, "tRNS chunk not allowed with alpha channel");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (png_crc_finish(png_ptr, 0))
   {
      png_ptr->num_trans = 0;
      return;
   }

   png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans,
      &(png_ptr->trans_values));
}