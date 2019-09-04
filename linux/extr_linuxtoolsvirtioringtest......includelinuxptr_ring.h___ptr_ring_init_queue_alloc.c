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
typedef  int gfp_t ;

/* Variables and functions */
 int KMALLOC_MAX_SIZE ; 
 int __GFP_ZERO ; 
 void** kvmalloc_array (unsigned int,int,int) ; 

__attribute__((used)) static inline void **__ptr_ring_init_queue_alloc(unsigned int size, gfp_t gfp)
{
	if (size > KMALLOC_MAX_SIZE / sizeof(void *))
		return NULL;
	return kvmalloc_array(size, sizeof(void *), gfp | __GFP_ZERO);
}