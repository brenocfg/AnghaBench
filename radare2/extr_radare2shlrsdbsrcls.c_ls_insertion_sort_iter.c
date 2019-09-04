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
struct TYPE_3__ {void* data; struct TYPE_3__* n; } ;
typedef  TYPE_1__ SdbListIter ;
typedef  scalar_t__ (* SdbListComparator ) (void*,void*) ;

/* Variables and functions */

__attribute__((used)) static void ls_insertion_sort_iter(SdbListIter *iter, SdbListComparator cmp) {
	SdbListIter *it, *it2;
	for (it = iter; it && it->data; it = it->n) {
		for (it2 = it->n; it2 && it2->data; it2 = it2->n) {
			if (cmp (it->data, it2->data) > 0) {
				void *t = it->data;
				it->data = it2->data;
				it2->data = t;
			}
		}
	}
}