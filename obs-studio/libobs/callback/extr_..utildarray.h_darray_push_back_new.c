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
struct darray {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 void* darray_end (size_t const,struct darray*) ; 
 int /*<<< orphan*/  darray_ensure_capacity (size_t const,struct darray*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static inline void *darray_push_back_new(const size_t element_size,
					 struct darray *dst)
{
	void *last;

	darray_ensure_capacity(element_size, dst, ++dst->num);

	last = darray_end(element_size, dst);
	memset(last, 0, element_size);
	return last;
}