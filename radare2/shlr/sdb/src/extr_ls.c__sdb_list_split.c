#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* n; } ;
typedef  TYPE_1__ SdbListIter ;

/* Variables and functions */

__attribute__((used)) static SdbListIter * _sdb_list_split(SdbListIter *head) {
	SdbListIter *tmp;
	SdbListIter *fast;
	SdbListIter *slow;
	if (!head || !head->n) {
		return head;
	} 
	slow = head;
	fast = head;
	while (fast && fast->n && fast->n->n) {
		fast = fast->n->n;
		slow = slow->n;
	}
	tmp = slow->n;
	slow->n = NULL;
	return tmp;
}