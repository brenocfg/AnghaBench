#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ce_flags; scalar_t__ type; size_t num_interfaces; struct TYPE_4__** interfaces; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  swap_func_t ;
typedef  int /*<<< orphan*/  compare_func_t ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ Bucket ;

/* Variables and functions */
 int ZEND_ACC_LINKED ; 
 scalar_t__ ZEND_USER_CLASS ; 
 TYPE_1__* Z_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void preload_sort_classes(void *base, size_t count, size_t siz, compare_func_t compare, swap_func_t swp) /* {{{ */
{
	Bucket *b1 = base;
	Bucket *b2;
	Bucket *end = b1 + count;
	Bucket tmp;
	zend_class_entry *ce, *p;

	while (b1 < end) {
try_again:
		ce = (zend_class_entry*)Z_PTR(b1->val);
		if (ce->parent && (ce->ce_flags & ZEND_ACC_LINKED)) {
			p = ce->parent;
			if (p->type == ZEND_USER_CLASS) {
				b2 = b1 + 1;
				while (b2 < end) {
					if (p ==  Z_PTR(b2->val)) {
						tmp = *b1;
						*b1 = *b2;
						*b2 = tmp;
						goto try_again;
					}
					b2++;
				}
			}
		}
		if (ce->num_interfaces && (ce->ce_flags & ZEND_ACC_LINKED)) {
			uint32_t i = 0;
			for (i = 0; i < ce->num_interfaces; i++) {
				p = ce->interfaces[i];
				if (p->type == ZEND_USER_CLASS) {
					b2 = b1 + 1;
					while (b2 < end) {
						if (p ==  Z_PTR(b2->val)) {
							tmp = *b1;
							*b1 = *b2;
							*b2 = tmp;
							goto try_again;
						}
						b2++;
					}
				}
			}
		}
		b1++;
	}
}