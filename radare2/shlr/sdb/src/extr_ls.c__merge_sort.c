#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ SdbListIter ;
typedef  int /*<<< orphan*/  SdbListComparator ;

/* Variables and functions */
 TYPE_1__* _merge (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* _sdb_list_split (TYPE_1__*) ; 

__attribute__((used)) static SdbListIter * _merge_sort(SdbListIter *head, SdbListComparator cmp) {
	SdbListIter *second;
	if (!head || !head->n) {
		return head;
	}
	second = _sdb_list_split (head);
	head = _merge_sort (head, cmp);
	second = _merge_sort (second, cmp);
	return _merge (head, second, cmp);
}