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
struct TYPE_3__ {int iter_active; int /*<<< orphan*/  iter_values_buf; int /*<<< orphan*/  iter_values; scalar_t__ iter_num_values; scalar_t__ iter_valueno; scalar_t__ iter_itemno; int /*<<< orphan*/  leftmost_leaf; int /*<<< orphan*/  iter_node; } ;
typedef  TYPE_1__ IntegerSet ;

/* Variables and functions */

void
intset_begin_iterate(IntegerSet *intset)
{
	/* Note that we allow an iteration to be abandoned midway */
	intset->iter_active = true;
	intset->iter_node = intset->leftmost_leaf;
	intset->iter_itemno = 0;
	intset->iter_valueno = 0;
	intset->iter_num_values = 0;
	intset->iter_values = intset->iter_values_buf;
}