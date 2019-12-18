#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_5__ {scalar_t__ num_chunk_list; int /*<<< orphan*/ * chunk_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FREE_ALL ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_free_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_info ; 
 int /*<<< orphan*/  png_info_init_3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_sizeof (int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_info_destroy(png_structp png_ptr, png_infop info_ptr)
{
   png_debug(1, "in png_info_destroy\n");

   png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED)
   if (png_ptr->num_chunk_list)
   {
       png_free(png_ptr, png_ptr->chunk_list);
       png_ptr->chunk_list=NULL;
       png_ptr->num_chunk_list=0;
   }
#endif

   png_info_init_3(&info_ptr, png_sizeof(png_info));
}