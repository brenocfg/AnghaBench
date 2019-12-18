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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  darray_erase (size_t const,struct darray*,scalar_t__) ; 

__attribute__((used)) static inline void darray_pop_back(const size_t element_size,
				   struct darray *dst)
{
	assert(dst->num != 0);

	if (dst->num)
		darray_erase(element_size, dst, dst->num - 1);
}