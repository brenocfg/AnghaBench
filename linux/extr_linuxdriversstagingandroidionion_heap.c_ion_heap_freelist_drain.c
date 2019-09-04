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
struct ion_heap {int dummy; } ;

/* Variables and functions */
 size_t _ion_heap_freelist_drain (struct ion_heap*,size_t,int) ; 

size_t ion_heap_freelist_drain(struct ion_heap *heap, size_t size)
{
	return _ion_heap_freelist_drain(heap, size, false);
}