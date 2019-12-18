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
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  void* png_size_t ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  char* png_charp ;
struct TYPE_6__ {int mode; int skip_length; char* current_text; char* current_text_ptr; int /*<<< orphan*/  process_mode; void* current_text_left; void* current_text_size; } ;

/* Variables and functions */
 int PNG_HAVE_IEND ; 
 int PNG_HAVE_IHDR ; 
 int /*<<< orphan*/  PNG_READ_tEXt_MODE ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 scalar_t__ png_malloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_push_handle_tEXt(png_structp png_ptr, png_infop info_ptr, png_uint_32
   length)
{
   if (!(png_ptr->mode & PNG_HAVE_IHDR) || (png_ptr->mode & PNG_HAVE_IEND))
      {
         png_error(png_ptr, "Out of place tEXt");
         info_ptr = info_ptr; /* to quiet some compiler warnings */
      }

#ifdef PNG_MAX_MALLOC_64K
   png_ptr->skip_length = 0;  /* This may not be necessary */

   if (length > (png_uint_32)65535L) /* Can't hold entire string in memory */
   {
      png_warning(png_ptr, "tEXt chunk too large to fit in memory");
      png_ptr->skip_length = length - (png_uint_32)65535L;
      length = (png_uint_32)65535L;
   }
#endif

   png_ptr->current_text = (png_charp)png_malloc(png_ptr,
         (png_uint_32)(length+1));
   png_ptr->current_text[length] = '\0';
   png_ptr->current_text_ptr = png_ptr->current_text;
   png_ptr->current_text_size = (png_size_t)length;
   png_ptr->current_text_left = (png_size_t)length;
   png_ptr->process_mode = PNG_READ_tEXt_MODE;
}