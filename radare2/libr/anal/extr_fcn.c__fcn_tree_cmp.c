#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_5__ {scalar_t__ max; scalar_t__ min; } ;
struct TYPE_6__ {scalar_t__ addr; TYPE_1__ meta; } ;
typedef  int /*<<< orphan*/  RBNode ;
typedef  TYPE_2__ RAnalFunction ;

/* Variables and functions */
 TYPE_2__* FCN_CONTAINER (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_meta_if_needed (TYPE_2__*) ; 

__attribute__((used)) static int _fcn_tree_cmp(const void *a_, const RBNode *b_, void *user) {
	const RAnalFunction *a = (const RAnalFunction *)a_;
	const RAnalFunction *b = FCN_CONTAINER (b_);
	set_meta_if_needed ((RAnalFunction *)a);
	set_meta_if_needed ((RAnalFunction *)b);
	ut32 size0 = a->meta.max - a->meta.min, size1 = b->meta.max - b->meta.min;
	ut64 from0 = a->meta.min, to0 = a->meta.min + size0, addr0 = a->addr;
	ut64 from1 = b->meta.min, to1 = b->meta.min + size1, addr1 = b->addr;
	if (from0 != from1) {
		return from0 < from1 ? -1 : 1;
	}
	if (to0 != to1) {
		return to0 - 1 < to1 - 1 ? -1 : 1;
	}
	if (addr0 != addr1) {
		return addr0 < addr1 ? -1 : 1;
	}
	return 0;
}