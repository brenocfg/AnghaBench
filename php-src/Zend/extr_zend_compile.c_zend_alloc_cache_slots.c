#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int cache_size; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 TYPE_1__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_op_array ; 

__attribute__((used)) static inline uint32_t zend_alloc_cache_slots(unsigned count) {
	if (count == 0) {
		return (uint32_t) -1;
	}

	zend_op_array *op_array = CG(active_op_array);
	uint32_t ret = op_array->cache_size;
	op_array->cache_size += count * sizeof(void*);
	return ret;
}