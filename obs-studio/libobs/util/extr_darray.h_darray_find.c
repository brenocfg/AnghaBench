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
struct darray {size_t const num; } ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 void* darray_item (size_t const,struct darray const*,size_t) ; 
 scalar_t__ memcmp (void*,void const*,size_t const) ; 

__attribute__((used)) static inline size_t darray_find(const size_t element_size,
				 const struct darray *da, const void *item,
				 const size_t idx)
{
	size_t i;

	assert(idx <= da->num);

	for (i = idx; i < da->num; i++) {
		void *compare = darray_item(element_size, da, i);
		if (memcmp(compare, item, element_size) == 0)
			return i;
	}

	return DARRAY_INVALID;
}