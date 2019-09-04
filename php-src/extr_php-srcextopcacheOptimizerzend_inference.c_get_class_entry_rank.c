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
struct TYPE_3__ {int ce_flags; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int ZEND_ACC_LINKED ; 

__attribute__((used)) static uint32_t get_class_entry_rank(zend_class_entry *ce) {
	uint32_t rank = 0;
	if (ce->ce_flags & ZEND_ACC_LINKED) {
		while (ce->parent) {
			rank++;
			ce = ce->parent;
		}
	}
	return rank;
}