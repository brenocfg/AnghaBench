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
struct darray {int dummy; } ;

/* Variables and functions */
 void* darray_item (size_t const,struct darray*,size_t const) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t const) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t const) ; 

__attribute__((used)) static inline void darray_move_item(const size_t element_size,
				    struct darray *dst, const size_t from,
				    const size_t to)
{
	void *temp, *p_from, *p_to;

	if (from == to)
		return;

	temp = malloc(element_size);
	p_from = darray_item(element_size, dst, from);
	p_to = darray_item(element_size, dst, to);

	memcpy(temp, p_from, element_size);

	if (to < from)
		memmove(darray_item(element_size, dst, to + 1), p_to,
			element_size * (from - to));
	else
		memmove(p_from, darray_item(element_size, dst, from + 1),
			element_size * (to - from));

	memcpy(p_to, temp, element_size);
	free(temp);
}