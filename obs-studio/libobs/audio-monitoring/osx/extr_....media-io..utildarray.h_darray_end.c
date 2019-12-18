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
struct darray {scalar_t__ num; } ;

/* Variables and functions */
 void* darray_item (size_t const,struct darray const*,scalar_t__) ; 

__attribute__((used)) static inline void *darray_end(const size_t element_size,
			       const struct darray *da)
{
	if (!da->num)
		return NULL;

	return darray_item(element_size, da, da->num - 1);
}