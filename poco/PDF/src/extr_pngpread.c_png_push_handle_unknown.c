#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  png_charp ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_16__ {char* name; int /*<<< orphan*/ * data; scalar_t__ size; } ;
struct TYPE_15__ {int* chunk_name; int (* read_user_chunk_fn ) (TYPE_1__*,TYPE_3__*) ;int flags; TYPE_3__ unknown_chunk; } ;

/* Variables and functions */
 int PNG_FLAG_KEEP_UNKNOWN_CHUNKS ; 
 scalar_t__ PNG_HANDLE_CHUNK_ALWAYS ; 
 int /*<<< orphan*/  png_check_chunk_name (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ png_handle_as_unknown (TYPE_1__*,int*) ; 
 scalar_t__ png_malloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_push_crc_skip (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  png_set_unknown_chunks (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int png_sizeof (char*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int stub1 (TYPE_1__*,TYPE_3__*) ; 

void /* PRIVATE */
png_push_handle_unknown(png_structp png_ptr, png_infop info_ptr, png_uint_32
   length)
{
   png_uint_32 skip=0;
   png_check_chunk_name(png_ptr, png_ptr->chunk_name);

   if (!(png_ptr->chunk_name[0] & 0x20))
   {
#if defined(PNG_READ_UNKNOWN_CHUNKS_SUPPORTED)
     if(png_handle_as_unknown(png_ptr, png_ptr->chunk_name) !=
          PNG_HANDLE_CHUNK_ALWAYS
#if defined(PNG_READ_USER_CHUNKS_SUPPORTED)
          && png_ptr->read_user_chunk_fn == NULL
#endif
        )
#endif
        png_chunk_error(png_ptr, "unknown critical chunk");

     info_ptr = info_ptr; /* to quiet some compiler warnings */
   }

#if defined(PNG_READ_UNKNOWN_CHUNKS_SUPPORTED)
   if (png_ptr->flags & PNG_FLAG_KEEP_UNKNOWN_CHUNKS)
   {
#ifdef PNG_MAX_MALLOC_64K
      if (length > (png_uint_32)65535L)
      {
          png_warning(png_ptr, "unknown chunk too large to fit in memory");
          skip = length - (png_uint_32)65535L;
          length = (png_uint_32)65535L;
      }
#endif
      png_memcpy((png_charp)png_ptr->unknown_chunk.name,
                 (png_charp)png_ptr->chunk_name, 
                 png_sizeof(png_ptr->unknown_chunk.name));
      png_ptr->unknown_chunk.name[png_sizeof(png_ptr->unknown_chunk.name)-1]='\0';

      png_ptr->unknown_chunk.data = (png_bytep)png_malloc(png_ptr, length);
      png_ptr->unknown_chunk.size = (png_size_t)length;
      png_crc_read(png_ptr, (png_bytep)png_ptr->unknown_chunk.data, length);
#if defined(PNG_READ_USER_CHUNKS_SUPPORTED)
      if(png_ptr->read_user_chunk_fn != NULL)
      {
         /* callback to user unknown chunk handler */
         int ret;
         ret = (*(png_ptr->read_user_chunk_fn))
           (png_ptr, &png_ptr->unknown_chunk);
         if (ret < 0)
            png_chunk_error(png_ptr, "error in user chunk");
         if (ret == 0)
         {
            if (!(png_ptr->chunk_name[0] & 0x20))
               if(png_handle_as_unknown(png_ptr, png_ptr->chunk_name) !=
                    PNG_HANDLE_CHUNK_ALWAYS)
                  png_chunk_error(png_ptr, "unknown critical chunk");
            png_set_unknown_chunks(png_ptr, info_ptr,
               &png_ptr->unknown_chunk, 1);
         }
      }
#else
      png_set_unknown_chunks(png_ptr, info_ptr, &png_ptr->unknown_chunk, 1);
#endif
      png_free(png_ptr, png_ptr->unknown_chunk.data);
      png_ptr->unknown_chunk.data = NULL;
   }
   else
#endif
      skip=length;
   png_push_crc_skip(png_ptr, skip);
}