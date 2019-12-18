#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  TYPE_2__* png_infop ;
typedef  scalar_t__ png_fixed_point ;
typedef  int png_byte ;
struct TYPE_12__ {int valid; int gamma; scalar_t__ int_y_blue; scalar_t__ int_x_blue; scalar_t__ int_y_green; scalar_t__ int_x_green; scalar_t__ int_y_red; scalar_t__ int_x_red; scalar_t__ int_y_white; scalar_t__ int_x_white; scalar_t__ int_gamma; } ;
struct TYPE_11__ {int mode; int gamma; scalar_t__ int_gamma; } ;

/* Variables and functions */
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_INFO_cHRM ; 
 int PNG_INFO_gAMA ; 
 int PNG_INFO_sRGB ; 
 scalar_t__ PNG_OUT_OF_RANGE (scalar_t__,int,int) ; 
 int PNG_sRGB_INTENT_LAST ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_set_sRGB_gAMA_and_cHRM (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void /* PRIVATE */
png_handle_sRGB(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   int intent;
   png_byte buf[1];

   png_debug(1, "in png_handle_sRGB\n");

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before sRGB");
   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid sRGB after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }
   else if (png_ptr->mode & PNG_HAVE_PLTE)
      /* Should be an error, but we can cope with it */
      png_warning(png_ptr, "Out of place sRGB chunk");

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_sRGB))
   {
      png_warning(png_ptr, "Duplicate sRGB chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (length != 1)
   {
      png_warning(png_ptr, "Incorrect sRGB chunk length");
      png_crc_finish(png_ptr, length);
      return;
   }

   png_crc_read(png_ptr, buf, 1);
   if (png_crc_finish(png_ptr, 0))
      return;

   intent = buf[0];
   /* check for bad intent */
   if (intent >= PNG_sRGB_INTENT_LAST)
   {
      png_warning(png_ptr, "Unknown sRGB intent");
      return;
   }

#if defined(PNG_READ_gAMA_SUPPORTED) && defined(PNG_READ_GAMMA_SUPPORTED)
   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_gAMA))
   {
   png_fixed_point igamma;
#ifdef PNG_FIXED_POINT_SUPPORTED
      igamma=info_ptr->int_gamma;
#else
#  ifdef PNG_FLOATING_POINT_SUPPORTED
      igamma=(png_fixed_point)(info_ptr->gamma * 100000.);
#  endif
#endif
      if (PNG_OUT_OF_RANGE(igamma, 45500L, 500))
      {
         png_warning(png_ptr,
           "Ignoring incorrect gAMA value when sRGB is also present");
#ifndef PNG_NO_CONSOLE_IO
#  ifdef PNG_FIXED_POINT_SUPPORTED
         fprintf(stderr,"incorrect gamma=(%d/100000)\n",(int)png_ptr->int_gamma);
#  else
#    ifdef PNG_FLOATING_POINT_SUPPORTED
         fprintf(stderr,"incorrect gamma=%f\n",png_ptr->gamma);
#    endif
#  endif
#endif
      }
   }
#endif /* PNG_READ_gAMA_SUPPORTED */

#ifdef PNG_READ_cHRM_SUPPORTED
#ifdef PNG_FIXED_POINT_SUPPORTED
   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_cHRM))
      if (PNG_OUT_OF_RANGE(info_ptr->int_x_white, 31270,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_y_white, 32900,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_x_red,   64000L, 1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_y_red,   33000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_x_green, 30000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_y_green, 60000L, 1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_x_blue,  15000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->int_y_blue,   6000,  1000))
         {
            png_warning(png_ptr,
              "Ignoring incorrect cHRM value when sRGB is also present");
         }
#endif /* PNG_FIXED_POINT_SUPPORTED */
#endif /* PNG_READ_cHRM_SUPPORTED */

   png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, intent);
}