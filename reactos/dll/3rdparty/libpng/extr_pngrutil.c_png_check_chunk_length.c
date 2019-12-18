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
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_const_structrp ;
typedef  scalar_t__ png_alloc_size_t ;
struct TYPE_4__ {scalar_t__ user_chunk_malloc_max; scalar_t__ chunk_name; int bit_depth; size_t height; scalar_t__ interlaced; scalar_t__ channels; scalar_t__ width; } ;

/* Variables and functions */
 scalar_t__ PNG_UINT_31_MAX ; 
 size_t PNG_UINT_32_MAX ; 
 scalar_t__ PNG_USER_CHUNK_MALLOC_MAX ; 
 scalar_t__ png_IDAT ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_debug2 (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 

void /* PRIVATE */
png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
   png_alloc_size_t limit = PNG_UINT_31_MAX;

# ifdef PNG_SET_USER_LIMITS_SUPPORTED
   if (png_ptr->user_chunk_malloc_max > 0 &&
       png_ptr->user_chunk_malloc_max < limit)
      limit = png_ptr->user_chunk_malloc_max;
# elif PNG_USER_CHUNK_MALLOC_MAX > 0
   if (PNG_USER_CHUNK_MALLOC_MAX < limit)
      limit = PNG_USER_CHUNK_MALLOC_MAX;
# endif
   if (png_ptr->chunk_name == png_IDAT)
   {
      png_alloc_size_t idat_limit = PNG_UINT_31_MAX;
      size_t row_factor =
         (size_t)png_ptr->width
         * (size_t)png_ptr->channels
         * (png_ptr->bit_depth > 8? 2: 1)
         + 1
         + (png_ptr->interlaced? 6: 0);
      if (png_ptr->height > PNG_UINT_32_MAX/row_factor)
         idat_limit = PNG_UINT_31_MAX;
      else
         idat_limit = png_ptr->height * row_factor;
      row_factor = row_factor > 32566? 32566 : row_factor;
      idat_limit += 6 + 5*(idat_limit/row_factor+1); /* zlib+deflate overhead */
      idat_limit=idat_limit < PNG_UINT_31_MAX? idat_limit : PNG_UINT_31_MAX;
      limit = limit < idat_limit? idat_limit : limit;
   }

   if (length > limit)
   {
      png_debug2(0," length = %lu, limit = %lu",
         (unsigned long)length,(unsigned long)limit);
      png_chunk_error(png_ptr, "chunk data is too large");
   }
}