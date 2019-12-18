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
struct TYPE_3__ {scalar_t__ label; } ;
typedef  TYPE_1__ pending_label ;
typedef  scalar_t__ XactEvent ;

/* Variables and functions */
 char* MemoryContextStrdup (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 scalar_t__ XACT_EVENT_ABORT ; 
 scalar_t__ XACT_EVENT_COMMIT ; 
 char* client_label_committed ; 
 scalar_t__ client_label_pending ; 
 TYPE_1__* llast (scalar_t__) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
sepgsql_xact_callback(XactEvent event, void *arg)
{
	if (event == XACT_EVENT_COMMIT)
	{
		if (client_label_pending != NIL)
		{
			pending_label *plabel = llast(client_label_pending);
			char	   *new_label;

			if (plabel->label)
				new_label = MemoryContextStrdup(TopMemoryContext,
												plabel->label);
			else
				new_label = NULL;

			if (client_label_committed)
				pfree(client_label_committed);

			client_label_committed = new_label;

			/*
			 * XXX - Note that items of client_label_pending are allocated on
			 * CurTransactionContext, thus, all acquired memory region shall
			 * be released implicitly.
			 */
			client_label_pending = NIL;
		}
	}
	else if (event == XACT_EVENT_ABORT)
		client_label_pending = NIL;
}