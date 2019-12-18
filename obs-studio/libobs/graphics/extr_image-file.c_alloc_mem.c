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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  gs_image_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 void* bzalloc (size_t) ; 

__attribute__((used)) static inline void *alloc_mem(gs_image_file_t *image, uint64_t *mem_usage,
			      size_t size)
{
	UNUSED_PARAMETER(image);

	if (mem_usage)
		*mem_usage += size;
	return bzalloc(size);
}