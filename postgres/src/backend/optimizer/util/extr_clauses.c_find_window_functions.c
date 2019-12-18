#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maxWinRef; int /*<<< orphan*/ ** windowFuncs; scalar_t__ numWindowFuncs; } ;
typedef  TYPE_1__ WindowFuncLists ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int Index ;

/* Variables and functions */
 int /*<<< orphan*/  find_window_functions_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

WindowFuncLists *
find_window_functions(Node *clause, Index maxWinRef)
{
	WindowFuncLists *lists = palloc(sizeof(WindowFuncLists));

	lists->numWindowFuncs = 0;
	lists->maxWinRef = maxWinRef;
	lists->windowFuncs = (List **) palloc0((maxWinRef + 1) * sizeof(List *));
	(void) find_window_functions_walker(clause, lists);
	return lists;
}