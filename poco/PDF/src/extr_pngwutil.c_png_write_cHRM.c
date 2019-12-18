#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_cHRM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,double) ; 
 int /*<<< orphan*/  png_cHRM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_save_uint_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_write_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void /* PRIVATE */
png_write_cHRM(png_structp png_ptr, double white_x, double white_y,
   double red_x, double red_y, double green_x, double green_y,
   double blue_x, double blue_y)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_cHRM;
#endif
   png_byte buf[32];
   png_uint_32 itemp;

   png_debug(1, "in png_write_cHRM\n");
   /* each value is saved in 1/100,000ths */
   if (white_x < 0 || white_x > 0.8 || white_y < 0 || white_y > 0.8 ||
       white_x + white_y > 1.0)
   {
      png_warning(png_ptr, "Invalid cHRM white point specified");
#if !defined(PNG_NO_CONSOLE_IO)
      fprintf(stderr,"white_x=%f, white_y=%f\n",white_x, white_y);
#endif
      return;
   }
   itemp = (png_uint_32)(white_x * 100000.0 + 0.5);
   png_save_uint_32(buf, itemp);
   itemp = (png_uint_32)(white_y * 100000.0 + 0.5);
   png_save_uint_32(buf + 4, itemp);

   if (red_x < 0 ||  red_y < 0 || red_x + red_y > 1.0)
   {
      png_warning(png_ptr, "Invalid cHRM red point specified");
      return;
   }
   itemp = (png_uint_32)(red_x * 100000.0 + 0.5);
   png_save_uint_32(buf + 8, itemp);
   itemp = (png_uint_32)(red_y * 100000.0 + 0.5);
   png_save_uint_32(buf + 12, itemp);

   if (green_x < 0 || green_y < 0 || green_x + green_y > 1.0)
   {
      png_warning(png_ptr, "Invalid cHRM green point specified");
      return;
   }
   itemp = (png_uint_32)(green_x * 100000.0 + 0.5);
   png_save_uint_32(buf + 16, itemp);
   itemp = (png_uint_32)(green_y * 100000.0 + 0.5);
   png_save_uint_32(buf + 20, itemp);

   if (blue_x < 0 || blue_y < 0 || blue_x + blue_y > 1.0)
   {
      png_warning(png_ptr, "Invalid cHRM blue point specified");
      return;
   }
   itemp = (png_uint_32)(blue_x * 100000.0 + 0.5);
   png_save_uint_32(buf + 24, itemp);
   itemp = (png_uint_32)(blue_y * 100000.0 + 0.5);
   png_save_uint_32(buf + 28, itemp);

   png_write_chunk(png_ptr, png_cHRM, buf, (png_size_t)32);
}