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

/* Variables and functions */
 int GFP_NOFS ; 
 unsigned int KMALLOC_MAX_SIZE ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_NOWARN ; 
 void* __vmalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 void* kmalloc (unsigned int,int) ; 

__attribute__((used)) static void *gfs2_alloc_sort_buffer(unsigned size)
{
	void *ptr = NULL;

	if (size < KMALLOC_MAX_SIZE)
		ptr = kmalloc(size, GFP_NOFS | __GFP_NOWARN);
	if (!ptr)
		ptr = __vmalloc(size, GFP_NOFS, PAGE_KERNEL);
	return ptr;
}