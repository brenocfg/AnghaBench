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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RGraphVisitor ;
typedef  int /*<<< orphan*/  RGraphNode ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_sorted(RGraphNode *n, RGraphVisitor *vis) {
	RList *l = (RList *) vis->data;
	r_list_prepend (l, n);
}