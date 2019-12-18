#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  void* png_size_t ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  char* png_charp ;
struct TYPE_7__ {int mode; char* current_text; char* current_text_ptr; int /*<<< orphan*/  process_mode; void* current_text_left; void* current_text_size; } ;

/* Variables and functions */
 int PNG_HAVE_IEND ; 
 int PNG_HAVE_IHDR ; 
 int /*<<< orphan*/  PNG_READ_zTXt_MODE ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 scalar_t__ png_malloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_push_crc_skip (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_push_handle_zTXt(png_structp png_ptr, png_infop info_ptr, png_uint_32
   length)
{
   if (!(png_ptr->mode & PNG_HAVE_IHDR) || (png_ptr->mode & PNG_HAVE_IEND))
      {
         png_error(png_ptr, "Out of place zTXt");
         info_ptr = info_ptr; /* to quiet some compiler warnings */
      }

#ifdef PNG_MAX_MALLOC_64K
   /* We can't handle zTXt chunks > 64K, since we don't have enough space
    * to be able to store the uncompressed data.  Actually, the threshold
    * is probably around 32K, but it isn't as definite as 64K is.
    */
   if (length > (png_uint_32)65535L)
   {
      png_warning(png_ptr, "zTXt chunk too large to fit in memory");
      png_push_crc_skip(png_ptr, length);
      return;
   }
#endif

   png_ptr->current_text = (png_charp)png_malloc(png_ptr,
       (png_uint_32)(length+1));
   png_ptr->current_text[length] = '\0';
   png_ptr->current_text_ptr = png_ptr->current_text;
   png_ptr->current_text_size = (png_size_t)length;
   png_ptr->current_text_left = (png_size_t)length;
   png_ptr->process_mode = PNG_READ_zTXt_MODE;
}