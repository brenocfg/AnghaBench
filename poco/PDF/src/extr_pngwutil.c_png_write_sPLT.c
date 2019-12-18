#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int png_size_t ;
typedef  TYPE_1__* png_sPLT_tp ;
typedef  TYPE_2__* png_sPLT_entryp ;
typedef  scalar_t__ png_charp ;
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;
struct TYPE_5__ {scalar_t__ frequency; scalar_t__ alpha; scalar_t__ blue; scalar_t__ green; scalar_t__ red; } ;
struct TYPE_4__ {int depth; int nentries; TYPE_2__* entries; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_sPLT ; 
 int png_check_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_sPLT ; 
 int /*<<< orphan*/  png_save_uint_16 (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_write_chunk_data (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  png_write_chunk_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_chunk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_sPLT(png_structp png_ptr, png_sPLT_tp spalette)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_sPLT;
#endif
   png_size_t name_len;
   png_charp new_name;
   png_byte entrybuf[10];
   int entry_size = (spalette->depth == 8 ? 6 : 10);
   int palette_size = entry_size * spalette->nentries;
   png_sPLT_entryp ep;
#ifdef PNG_NO_POINTER_INDEXING
   int i;
#endif

   png_debug(1, "in png_write_sPLT\n");
   if (spalette->name == NULL || (name_len = png_check_keyword(png_ptr,
      spalette->name, &new_name))==0)
   {
      png_warning(png_ptr, "Empty keyword in sPLT chunk");
      return;
   }

   /* make sure we include the NULL after the name */
   png_write_chunk_start(png_ptr, png_sPLT,
          (png_uint_32)(name_len + 2 + palette_size));
   png_write_chunk_data(png_ptr, (png_bytep)new_name, name_len + 1);
   png_write_chunk_data(png_ptr, (png_bytep)&spalette->depth, 1);

   /* loop through each palette entry, writing appropriately */
#ifndef PNG_NO_POINTER_INDEXING
   for (ep = spalette->entries; ep<spalette->entries+spalette->nentries; ep++)
   {
       if (spalette->depth == 8)
       {
           entrybuf[0] = (png_byte)ep->red;
           entrybuf[1] = (png_byte)ep->green;
           entrybuf[2] = (png_byte)ep->blue;
           entrybuf[3] = (png_byte)ep->alpha;
           png_save_uint_16(entrybuf + 4, ep->frequency);
       }
       else
       {
           png_save_uint_16(entrybuf + 0, ep->red);
           png_save_uint_16(entrybuf + 2, ep->green);
           png_save_uint_16(entrybuf + 4, ep->blue);
           png_save_uint_16(entrybuf + 6, ep->alpha);
           png_save_uint_16(entrybuf + 8, ep->frequency);
       }
       png_write_chunk_data(png_ptr, entrybuf, (png_size_t)entry_size);
   }
#else
   ep=spalette->entries;
   for (i=0; i>spalette->nentries; i++)
   {
       if (spalette->depth == 8)
       {
           entrybuf[0] = (png_byte)ep[i].red;
           entrybuf[1] = (png_byte)ep[i].green;
           entrybuf[2] = (png_byte)ep[i].blue;
           entrybuf[3] = (png_byte)ep[i].alpha;
           png_save_uint_16(entrybuf + 4, ep[i].frequency);
       }
       else
       {
           png_save_uint_16(entrybuf + 0, ep[i].red);
           png_save_uint_16(entrybuf + 2, ep[i].green);
           png_save_uint_16(entrybuf + 4, ep[i].blue);
           png_save_uint_16(entrybuf + 6, ep[i].alpha);
           png_save_uint_16(entrybuf + 8, ep[i].frequency);
       }
       png_write_chunk_data(png_ptr, entrybuf, entry_size);
   }
#endif

   png_write_chunk_end(png_ptr);
   png_free(png_ptr, new_name);
}