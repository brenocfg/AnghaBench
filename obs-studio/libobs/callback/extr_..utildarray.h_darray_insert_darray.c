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
 int /*<<< orphan*/  darray_insert_array (size_t const,struct darray*,size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void darray_insert_darray(const size_t element_size,
					struct darray *dst, const size_t idx,
					const struct darray *da)
{
	darray_insert_array(element_size, dst, idx, da->array, da->num);
}