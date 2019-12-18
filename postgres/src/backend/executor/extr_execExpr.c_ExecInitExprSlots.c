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
struct TYPE_4__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ LastAttnumInfo ;
typedef  int /*<<< orphan*/  ExprState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecPushExprSlots (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  get_last_attnums_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
ExecInitExprSlots(ExprState *state, Node *node)
{
	LastAttnumInfo info = {0, 0, 0};

	/*
	 * Figure out which attributes we're going to need.
	 */
	get_last_attnums_walker(node, &info);

	ExecPushExprSlots(state, &info);
}