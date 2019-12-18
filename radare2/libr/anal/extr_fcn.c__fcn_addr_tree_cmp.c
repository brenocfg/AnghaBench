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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  RBNode ;
typedef  TYPE_1__ RAnalFunction ;

/* Variables and functions */
 TYPE_1__* ADDR_FCN_CONTAINER (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int _fcn_addr_tree_cmp(const void *a_, const RBNode *b_, void *user) {
	const RAnalFunction *a = (const RAnalFunction *)a_;
	const RAnalFunction *b = ADDR_FCN_CONTAINER (b_);
	ut64 from0 = a->addr, from1 = b->addr;
	if (from0 != from1) {
		return from0 < from1 ? -1 : 1;
	}
	return 0;
}