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
struct darray {size_t const num; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  darray_free (struct darray*) ; 
 int /*<<< orphan*/  darray_resize (size_t const,struct darray*,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static inline void darray_copy(const size_t element_size, struct darray *dst,
			       const struct darray *da)
{
	if (da->num == 0) {
		darray_free(dst);
	} else {
		darray_resize(element_size, dst, da->num);
		memcpy(dst->array, da->array, element_size * da->num);
	}
}