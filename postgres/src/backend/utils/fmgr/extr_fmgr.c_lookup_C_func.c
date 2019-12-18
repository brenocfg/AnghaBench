#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ fn_xmin; int /*<<< orphan*/  fn_tid; } ;
struct TYPE_8__ {int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;
typedef  TYPE_3__ CFuncHashTabEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * CFuncHash ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ HeapTupleHeaderGetRawXmin (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CFuncHashTabEntry *
lookup_C_func(HeapTuple procedureTuple)
{
	Oid			fn_oid = ((Form_pg_proc) GETSTRUCT(procedureTuple))->oid;
	CFuncHashTabEntry *entry;

	if (CFuncHash == NULL)
		return NULL;			/* no table yet */
	entry = (CFuncHashTabEntry *)
		hash_search(CFuncHash,
					&fn_oid,
					HASH_FIND,
					NULL);
	if (entry == NULL)
		return NULL;			/* no such entry */
	if (entry->fn_xmin == HeapTupleHeaderGetRawXmin(procedureTuple->t_data) &&
		ItemPointerEquals(&entry->fn_tid, &procedureTuple->t_self))
		return entry;			/* OK */
	return NULL;				/* entry is out of date */
}