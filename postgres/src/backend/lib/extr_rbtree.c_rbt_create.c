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
typedef  int /*<<< orphan*/  rbt_freefunc ;
typedef  int /*<<< orphan*/  rbt_comparator ;
typedef  int /*<<< orphan*/  rbt_combiner ;
typedef  int /*<<< orphan*/  rbt_allocfunc ;
struct TYPE_3__ {int node_size; void* arg; int /*<<< orphan*/  freefunc; int /*<<< orphan*/  allocfunc; int /*<<< orphan*/  combiner; int /*<<< orphan*/  comparator; int /*<<< orphan*/  root; } ;
typedef  int Size ;
typedef  TYPE_1__ RBTree ;
typedef  int /*<<< orphan*/  RBTNode ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  RBTNIL ; 
 scalar_t__ palloc (int) ; 

RBTree *
rbt_create(Size node_size,
		   rbt_comparator comparator,
		   rbt_combiner combiner,
		   rbt_allocfunc allocfunc,
		   rbt_freefunc freefunc,
		   void *arg)
{
	RBTree	   *tree = (RBTree *) palloc(sizeof(RBTree));

	Assert(node_size > sizeof(RBTNode));

	tree->root = RBTNIL;
	tree->node_size = node_size;
	tree->comparator = comparator;
	tree->combiner = combiner;
	tree->allocfunc = allocfunc;
	tree->freefunc = freefunc;

	tree->arg = arg;

	return tree;
}