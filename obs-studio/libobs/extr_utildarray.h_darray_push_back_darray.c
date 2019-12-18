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
struct darray {int /*<<< orphan*/  num; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 size_t darray_push_back_array (size_t const,struct darray*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t darray_push_back_darray(const size_t element_size,
					     struct darray *dst,
					     const struct darray *da)
{
	return darray_push_back_array(element_size, dst, da->array, da->num);
}