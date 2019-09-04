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
typedef  int /*<<< orphan*/ * png_voidp ;
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  size_t png_alloc_size_t ;

/* Variables and functions */
 size_t PNG_SIZE_MAX ; 
 int /*<<< orphan*/ * png_malloc_base (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static png_voidp
png_malloc_array_checked(png_const_structrp png_ptr, int nelements,
    size_t element_size)
{
   png_alloc_size_t req = (png_alloc_size_t)nelements; /* known to be > 0 */

   if (req <= PNG_SIZE_MAX/element_size)
      return png_malloc_base(png_ptr, req * element_size);

   /* The failure case when the request is too large */
   return NULL;
}