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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  darray_item (size_t const,struct darray*,size_t const) ; 
 int /*<<< orphan*/  darray_resize (size_t const,struct darray*,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t const) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static inline void darray_insert_array(const size_t element_size,
				       struct darray *dst, const size_t idx,
				       const void *array, const size_t num)
{
	size_t old_num;

	assert(array != NULL);
	assert(num != 0);
	assert(idx < dst->num);

	old_num = dst->num;
	darray_resize(element_size, dst, dst->num + num);

	memmove(darray_item(element_size, dst, idx + num),
		darray_item(element_size, dst, idx),
		element_size * (old_num - idx));
	memcpy(darray_item(element_size, dst, idx), array, element_size * num);
}