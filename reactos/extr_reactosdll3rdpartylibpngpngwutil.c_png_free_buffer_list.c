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
typedef  int /*<<< orphan*/  png_structrp ;
typedef  TYPE_1__* png_compression_bufferp ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void /* PRIVATE */
png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *listp)
{
   png_compression_bufferp list = *listp;

   if (list != NULL)
   {
      *listp = NULL;

      do
      {
         png_compression_bufferp next = list->next;

         png_free(png_ptr, list);
         list = next;
      }
      while (list != NULL);
   }
}