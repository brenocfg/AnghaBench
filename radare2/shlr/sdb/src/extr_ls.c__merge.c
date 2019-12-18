#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* n; struct TYPE_5__* p; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ SdbListIter ;
typedef  scalar_t__ (* SdbListComparator ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */

__attribute__((used)) static SdbListIter *_merge(SdbListIter *first, SdbListIter *second, SdbListComparator cmp) {
	SdbListIter *next = NULL, *result = NULL, *head = NULL;
	while (first || second) {
		if (!second) {
			next = first;
			first = first->n;
		} else if (!first) {
			next = second;
			second = second->n;
		} else if (cmp (first->data, second->data) < 0) {
			next = first;
			first = first->n;
		} else {
			next = second;
			second = second->n;
		}
		if (!head) {
			result = next;
			head = result;
			head->p = NULL;
		} else {
			result->n = next;
			next->p = result;
			result = result->n;
		}
	}
	head->p = NULL;
	next->n = NULL;
	return head;
}