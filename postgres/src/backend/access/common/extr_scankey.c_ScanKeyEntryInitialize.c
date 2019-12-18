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
struct TYPE_3__ {int sk_flags; int /*<<< orphan*/  sk_func; int /*<<< orphan*/  sk_argument; void* sk_collation; void* sk_subtype; int /*<<< orphan*/  sk_strategy; int /*<<< orphan*/  sk_attno; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RegProcedureIsValid (int /*<<< orphan*/ ) ; 
 int SK_SEARCHNOTNULL ; 
 int SK_SEARCHNULL ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ScanKeyEntryInitialize(ScanKey entry,
					   int flags,
					   AttrNumber attributeNumber,
					   StrategyNumber strategy,
					   Oid subtype,
					   Oid collation,
					   RegProcedure procedure,
					   Datum argument)
{
	entry->sk_flags = flags;
	entry->sk_attno = attributeNumber;
	entry->sk_strategy = strategy;
	entry->sk_subtype = subtype;
	entry->sk_collation = collation;
	entry->sk_argument = argument;
	if (RegProcedureIsValid(procedure))
	{
		fmgr_info(procedure, &entry->sk_func);
	}
	else
	{
		Assert(flags & (SK_SEARCHNULL | SK_SEARCHNOTNULL));
		MemSet(&entry->sk_func, 0, sizeof(entry->sk_func));
	}
}