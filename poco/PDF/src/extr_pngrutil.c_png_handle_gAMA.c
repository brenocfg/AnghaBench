#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  TYPE_2__* png_infop ;
typedef  scalar_t__ png_fixed_point ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_14__ {int valid; } ;
struct TYPE_13__ {int mode; float gamma; } ;

/* Variables and functions */
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_INFO_gAMA ; 
 int PNG_INFO_sRGB ; 
 scalar_t__ PNG_OUT_OF_RANGE (scalar_t__,long,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_gAMA (TYPE_1__*,TYPE_2__*,float) ; 
 int /*<<< orphan*/  png_set_gAMA_fixed (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void /* PRIVATE */
png_handle_gAMA(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   png_fixed_point igamma;
#ifdef PNG_FLOATING_POINT_SUPPORTED
   float file_gamma;
#endif
   png_byte buf[4];

   png_debug(1, "in png_handle_gAMA\n");

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before gAMA");
   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid gAMA after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }
   else if (png_ptr->mode & PNG_HAVE_PLTE)
      /* Should be an error, but we can cope with it */
      png_warning(png_ptr, "Out of place gAMA chunk");

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_gAMA)
#if defined(PNG_READ_sRGB_SUPPORTED)
      && !(info_ptr->valid & PNG_INFO_sRGB)
#endif
      )
   {
      png_warning(png_ptr, "Duplicate gAMA chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (length != 4)
   {
      png_warning(png_ptr, "Incorrect gAMA chunk length");
      png_crc_finish(png_ptr, length);
      return;
   }

   png_crc_read(png_ptr, buf, 4);
   if (png_crc_finish(png_ptr, 0))
      return;

   igamma = (png_fixed_point)png_get_uint_32(buf);
   /* check for zero gamma */
   if (igamma == 0)
      {
         png_warning(png_ptr,
           "Ignoring gAMA chunk with gamma=0");
         return;
      }

#if defined(PNG_READ_sRGB_SUPPORTED)
   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_sRGB))
      if (PNG_OUT_OF_RANGE(igamma, 45500L, 500))
      {
         png_warning(png_ptr,
           "Ignoring incorrect gAMA value when sRGB is also present");
#ifndef PNG_NO_CONSOLE_IO
         fprintf(stderr, "gamma = (%d/100000)\n", (int)igamma);
#endif
         return;
      }
#endif /* PNG_READ_sRGB_SUPPORTED */

#ifdef PNG_FLOATING_POINT_SUPPORTED
   file_gamma = (float)igamma / (float)100000.0;
#  ifdef PNG_READ_GAMMA_SUPPORTED
     png_ptr->gamma = file_gamma;
#  endif
     png_set_gAMA(png_ptr, info_ptr, file_gamma);
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
   png_set_gAMA_fixed(png_ptr, info_ptr, igamma);
#endif
}