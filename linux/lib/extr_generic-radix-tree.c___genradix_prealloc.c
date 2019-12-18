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
struct __genradix {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __genradix_ptr_alloc (struct __genradix*,size_t,int /*<<< orphan*/ ) ; 

int __genradix_prealloc(struct __genradix *radix, size_t size,
			gfp_t gfp_mask)
{
	size_t offset;

	for (offset = 0; offset < size; offset += PAGE_SIZE)
		if (!__genradix_ptr_alloc(radix, offset, gfp_mask))
			return -ENOMEM;

	return 0;
}