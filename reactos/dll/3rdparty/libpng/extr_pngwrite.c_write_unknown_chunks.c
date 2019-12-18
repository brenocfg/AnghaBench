#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  TYPE_2__* png_const_unknown_chunkp ;
typedef  TYPE_3__* png_const_inforp ;
struct TYPE_11__ {scalar_t__ unknown_chunks_num; TYPE_2__* unknown_chunks; } ;
struct TYPE_10__ {unsigned int location; int* name; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int unknown_default; } ;

/* Variables and functions */
 int PNG_HANDLE_CHUNK_ALWAYS ; 
 int PNG_HANDLE_CHUNK_AS_DEFAULT ; 
 int PNG_HANDLE_CHUNK_NEVER ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int png_handle_as_unknown (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_write_chunk (TYPE_1__*,int*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr,
    unsigned int where)
{
   if (info_ptr->unknown_chunks_num != 0)
   {
      png_const_unknown_chunkp up;

      png_debug(5, "writing extra chunks");

      for (up = info_ptr->unknown_chunks;
           up < info_ptr->unknown_chunks + info_ptr->unknown_chunks_num;
           ++up)
         if ((up->location & where) != 0)
      {
         /* If per-chunk unknown chunk handling is enabled use it, otherwise
          * just write the chunks the application has set.
          */
#ifdef PNG_SET_UNKNOWN_CHUNKS_SUPPORTED
         int keep = png_handle_as_unknown(png_ptr, up->name);

         /* NOTE: this code is radically different from the read side in the
          * matter of handling an ancillary unknown chunk.  In the read side
          * the default behavior is to discard it, in the code below the default
          * behavior is to write it.  Critical chunks are, however, only
          * written if explicitly listed or if the default is set to write all
          * unknown chunks.
          *
          * The default handling is also slightly weird - it is not possible to
          * stop the writing of all unsafe-to-copy chunks!
          *
          * TODO: REVIEW: this would seem to be a bug.
          */
         if (keep != PNG_HANDLE_CHUNK_NEVER &&
             ((up->name[3] & 0x20) /* safe-to-copy overrides everything */ ||
              keep == PNG_HANDLE_CHUNK_ALWAYS ||
              (keep == PNG_HANDLE_CHUNK_AS_DEFAULT &&
               png_ptr->unknown_default == PNG_HANDLE_CHUNK_ALWAYS)))
#endif
         {
            /* TODO: review, what is wrong with a zero length unknown chunk? */
            if (up->size == 0)
               png_warning(png_ptr, "Writing zero-length unknown chunk");

            png_write_chunk(png_ptr, up->name, up->data, up->size);
         }
      }
   }
}