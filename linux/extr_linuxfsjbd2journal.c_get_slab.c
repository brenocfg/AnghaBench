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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int JBD2_MAX_SLABS ; 
 struct kmem_cache** jbd2_slab ; 
 int order_base_2 (size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct kmem_cache *get_slab(size_t size)
{
	int i = order_base_2(size) - 10;

	BUG_ON(i >= JBD2_MAX_SLABS);
	if (unlikely(i < 0))
		i = 0;
	BUG_ON(jbd2_slab[i] == NULL);
	return jbd2_slab[i];
}