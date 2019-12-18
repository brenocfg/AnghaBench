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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_4__ {int /*<<< orphan*/  instrument; int /*<<< orphan*/ * (* ExecProcNodeReal ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  InstrStartNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InstrStopNode (int /*<<< orphan*/ ,double) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*) ; 

__attribute__((used)) static TupleTableSlot *
ExecProcNodeInstr(PlanState *node)
{
	TupleTableSlot *result;

	InstrStartNode(node->instrument);

	result = node->ExecProcNodeReal(node);

	InstrStopNode(node->instrument, TupIsNull(result) ? 0.0 : 1.0);

	return result;
}