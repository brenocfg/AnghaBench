#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {scalar_t__ nChildXids; char* name; scalar_t__ subTransactionId; int /*<<< orphan*/  fullTransactionId; int /*<<< orphan*/  state; int /*<<< orphan*/  blockState; int /*<<< orphan*/  nestingLevel; struct TYPE_6__* parent; int /*<<< orphan*/ * childXids; } ;
typedef  TYPE_2__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  BlockStateAsString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG5 ; 
 scalar_t__ PointerIsValid (char*) ; 
 int /*<<< orphan*/  TransStateAsString (int /*<<< orphan*/ ) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ currentCommandId ; 
 scalar_t__ currentCommandIdUsed ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ShowTransactionStateRec(const char *str, TransactionState s)
{
	StringInfoData buf;

	initStringInfo(&buf);

	if (s->nChildXids > 0)
	{
		int			i;

		appendStringInfo(&buf, ", children: %u", s->childXids[0]);
		for (i = 1; i < s->nChildXids; i++)
			appendStringInfo(&buf, " %u", s->childXids[i]);
	}

	if (s->parent)
		ShowTransactionStateRec(str, s->parent);

	/* use ereport to suppress computation if msg will not be printed */
	ereport(DEBUG5,
			(errmsg_internal("%s(%d) name: %s; blockState: %s; state: %s, xid/subid/cid: %u/%u/%u%s%s",
							 str, s->nestingLevel,
							 PointerIsValid(s->name) ? s->name : "unnamed",
							 BlockStateAsString(s->blockState),
							 TransStateAsString(s->state),
							 (unsigned int) XidFromFullTransactionId(s->fullTransactionId),
							 (unsigned int) s->subTransactionId,
							 (unsigned int) currentCommandId,
							 currentCommandIdUsed ? " (used)" : "",
							 buf.data)));

	pfree(buf.data);
}