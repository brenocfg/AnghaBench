#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; TYPE_1__** path; } ;
struct TYPE_7__ {struct TYPE_7__** child; } ;
typedef  TYPE_1__ RBNode ;
typedef  TYPE_2__ RBIter ;
typedef  int (* RBComparator ) (void*,TYPE_1__*,void*) ;

/* Variables and functions */

__attribute__((used)) static inline RBIter bound_iter(RBNode *x, void *data, RBComparator cmp, bool upper, bool backward, void *user) {
	RBIter it;
	it.len = 0;
	while (x) {
		int d = cmp (data, x, user);
		if (upper ? d < 0 : d <= 0) {
			if (!backward) {
				it.path[it.len++] = x;
			}
			x = x->child[0];
		} else {
			if (backward) {
				it.path[it.len++] = x;
			}
			x = x->child[1];
		}
	}
	return it;
}