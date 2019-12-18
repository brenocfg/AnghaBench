#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tmpcontext; TYPE_1__* phase; } ;
struct TYPE_4__ {int /*<<< orphan*/  evaltrans; } ;
typedef  TYPE_2__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEvalExprSwitchContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
advance_aggregates(AggState *aggstate)
{
	bool		dummynull;

	ExecEvalExprSwitchContext(aggstate->phase->evaltrans,
							  aggstate->tmpcontext,
							  &dummynull);
}