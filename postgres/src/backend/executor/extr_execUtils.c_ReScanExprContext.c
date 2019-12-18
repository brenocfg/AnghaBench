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
struct TYPE_4__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
typedef  TYPE_1__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShutdownExprContext (TYPE_1__*,int) ; 

void
ReScanExprContext(ExprContext *econtext)
{
	/* Call any registered callbacks */
	ShutdownExprContext(econtext, true);
	/* And clean up the memory used */
	MemoryContextReset(econtext->ecxt_per_tuple_memory);
}