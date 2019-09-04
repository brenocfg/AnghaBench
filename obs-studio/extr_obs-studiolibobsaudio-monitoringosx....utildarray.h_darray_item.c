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
typedef  int /*<<< orphan*/  uint8_t ;
struct darray {scalar_t__ array; } ;

/* Variables and functions */

__attribute__((used)) static inline void *darray_item(const size_t element_size,
		const struct darray *da, size_t idx)
{
	return (void*)(((uint8_t*)da->array) + element_size*idx);
}