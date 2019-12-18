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
struct TYPE_3__ {int /*<<< orphan*/  tree_walk; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  LeftRightWalk ; 
 int /*<<< orphan*/  rbt_begin_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ginBeginBAScan(BuildAccumulator *accum)
{
	rbt_begin_iterate(accum->tree, LeftRightWalk, &accum->tree_walk);
}