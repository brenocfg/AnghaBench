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
 int /*<<< orphan*/  darray_free (struct darray*) ; 
 int /*<<< orphan*/  darray_push_back_darray (size_t const,struct darray*,struct darray*) ; 

__attribute__((used)) static inline void darray_join(const size_t element_size, struct darray *dst,
			       struct darray *da)
{
	darray_push_back_darray(element_size, dst, da);
	darray_free(da);
}