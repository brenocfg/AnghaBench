#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gl_image {struct gl_image* Data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct gl_image*) ; 

void gl_free_image( struct gl_image *image )
{
   if (image->Data) {
      free(image->Data);
   }
   free(image);
}