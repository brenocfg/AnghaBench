#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int png_uint_32 ;
struct TYPE_12__ {int /*<<< orphan*/  text_length; scalar_t__* text; scalar_t__ itxt_length; int /*<<< orphan*/ * lang_key; int /*<<< orphan*/ * lang; scalar_t__* key; int /*<<< orphan*/  compression; } ;
typedef  TYPE_1__ png_text ;
typedef  TYPE_2__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  scalar_t__* png_charp ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_13__ {int user_chunk_cache_max; int mode; } ;

/* Variables and functions */
 int PNG_AFTER_IDAT ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int /*<<< orphan*/  PNG_TEXT_COMPRESSION_NONE ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_2__*,char*) ; 
 scalar_t__ png_crc_finish (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/ * png_read_buffer (TYPE_2__*,unsigned int,int) ; 
 scalar_t__ png_set_text_2 (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 

void /* PRIVATE */
png_handle_tEXt(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_text  text_info;
   png_bytep buffer;
   png_charp key;
   png_charp text;
   png_uint_32 skip = 0;

   png_debug(1, "in png_handle_tEXt");

#ifdef PNG_USER_LIMITS_SUPPORTED
   if (png_ptr->user_chunk_cache_max != 0)
   {
      if (png_ptr->user_chunk_cache_max == 1)
      {
         png_crc_finish(png_ptr, length);
         return;
      }

      if (--png_ptr->user_chunk_cache_max == 1)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "no space in chunk cache");
         return;
      }
   }
#endif

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   if ((png_ptr->mode & PNG_HAVE_IDAT) != 0)
      png_ptr->mode |= PNG_AFTER_IDAT;

#ifdef PNG_MAX_MALLOC_64K
   if (length > 65535U)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "too large to fit in memory");
      return;
   }
#endif

   buffer = png_read_buffer(png_ptr, length+1, 1/*warn*/);

   if (buffer == NULL)
   {
      png_chunk_benign_error(png_ptr, "out of memory");
      return;
   }

   png_crc_read(png_ptr, buffer, length);

   if (png_crc_finish(png_ptr, skip) != 0)
      return;

   key = (png_charp)buffer;
   key[length] = 0;

   for (text = key; *text; text++)
      /* Empty loop to find end of key */ ;

   if (text != key + length)
      text++;

   text_info.compression = PNG_TEXT_COMPRESSION_NONE;
   text_info.key = key;
   text_info.lang = NULL;
   text_info.lang_key = NULL;
   text_info.itxt_length = 0;
   text_info.text = text;
   text_info.text_length = strlen(text);

   if (png_set_text_2(png_ptr, info_ptr, &text_info, 1) != 0)
      png_warning(png_ptr, "Insufficient memory to process text chunk");
}