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

__attribute__((used)) static inline size_t darray_alloc_size(const size_t element_size,
		const struct darray *da)
{
	return element_size*da->num;
}