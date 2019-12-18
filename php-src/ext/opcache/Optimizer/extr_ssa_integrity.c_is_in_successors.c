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
typedef  int zend_bool ;
struct TYPE_3__ {int successors_count; int* successors; } ;
typedef  TYPE_1__ zend_basic_block ;

/* Variables and functions */

__attribute__((used)) static inline zend_bool is_in_successors(zend_basic_block *block, int check) {
	int s;
	for (s = 0; s < block->successors_count; s++) {
		if (block->successors[s] == check) {
			return 1;
		}
	}
	return 0;
}