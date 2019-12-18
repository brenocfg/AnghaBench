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
typedef  void* Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  fmgr_info_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ScanKeyEntryInitializeWithInfo(ScanKey entry,
							   int flags,
							   AttrNumber attributeNumber,
							   StrategyNumber strategy,
							   Oid subtype,
							   Oid collation,
							   FmgrInfo *finfo,
							   Datum argument)
{
	entry->sk_flags = flags;
	entry->sk_attno = attributeNumber;
	entry->sk_strategy = strategy;
	entry->sk_subtype = subtype;
	entry->sk_collation = collation;
	entry->sk_argument = argument;
	fmgr_info_copy(&entry->sk_func, finfo, CurrentMemoryContext);
}