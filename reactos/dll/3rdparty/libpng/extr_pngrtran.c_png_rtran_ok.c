#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_4__ {int flags; int mode; } ;

/* Variables and functions */
 int PNG_FLAG_DETECT_UNINITIALIZED ; 
 int PNG_FLAG_ROW_INIT ; 
 int PNG_HAVE_IHDR ; 
 int /*<<< orphan*/  png_app_error (TYPE_1__*,char*) ; 

__attribute__((used)) static int
png_rtran_ok(png_structrp png_ptr, int need_IHDR)
{
   if (png_ptr != NULL)
   {
      if ((png_ptr->flags & PNG_FLAG_ROW_INIT) != 0)
         png_app_error(png_ptr,
             "invalid after png_start_read_image or png_read_update_info");

      else if (need_IHDR && (png_ptr->mode & PNG_HAVE_IHDR) == 0)
         png_app_error(png_ptr, "invalid before the PNG header has been read");

      else
      {
         /* Turn on failure to initialize correctly for all transforms. */
         png_ptr->flags |= PNG_FLAG_DETECT_UNINITIALIZED;

         return 1; /* Ok */
      }
   }

   return 0; /* no png_error possible! */
}