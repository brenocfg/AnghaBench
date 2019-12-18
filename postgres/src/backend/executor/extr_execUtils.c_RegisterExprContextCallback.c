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
struct TYPE_5__ {TYPE_1__* ecxt_callbacks; int /*<<< orphan*/  ecxt_per_query_memory; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  arg; int /*<<< orphan*/  function; } ;
typedef  TYPE_1__ ExprContext_CB ;
typedef  int /*<<< orphan*/  ExprContextCallbackFunction ;
typedef  TYPE_2__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 

void
RegisterExprContextCallback(ExprContext *econtext,
							ExprContextCallbackFunction function,
							Datum arg)
{
	ExprContext_CB *ecxt_callback;

	/* Save the info in appropriate memory context */
	ecxt_callback = (ExprContext_CB *)
		MemoryContextAlloc(econtext->ecxt_per_query_memory,
						   sizeof(ExprContext_CB));

	ecxt_callback->function = function;
	ecxt_callback->arg = arg;

	/* link to front of list for appropriate execution order */
	ecxt_callback->next = econtext->ecxt_callbacks;
	econtext->ecxt_callbacks = ecxt_callback;
}