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
struct TYPE_5__ {scalar_t__ min; } ;
struct TYPE_6__ {scalar_t__ _size; TYPE_1__ meta; } ;
typedef  int /*<<< orphan*/  RBNode ;
typedef  TYPE_2__ RAnalFunction ;

/* Variables and functions */
 TYPE_2__* FCN_CONTAINER (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_meta_min_if_needed (TYPE_2__*) ; 

__attribute__((used)) static int _fcn_tree_cmp(const void *a_, const RBNode *b_) {
	const RAnalFunction *a = (const RAnalFunction *)a_;
	const RAnalFunction *b = FCN_CONTAINER (b_);
	set_meta_min_if_needed ((RAnalFunction *)a);
	set_meta_min_if_needed ((RAnalFunction *)b);
	ut64 from0 = a->meta.min, to0 = a->meta.min + a->_size,
		from1 = b->meta.min, to1 = b->meta.min + b->_size;
	if (from0 != from1) {
		return from0 < from1 ? -1 : 1;
	}
	if (to0 != to1) {
		return to0 - 1 < to1 - 1 ? -1 : 1;
	}
	return 0;
}