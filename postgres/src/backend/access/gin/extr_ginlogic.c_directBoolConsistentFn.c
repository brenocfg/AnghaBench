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
struct TYPE_3__ {int recheckCurItem; int* entryRes; int* extra_data; int* queryValues; int* queryCategories; int /*<<< orphan*/  nuserentries; int /*<<< orphan*/  query; int /*<<< orphan*/  strategy; int /*<<< orphan*/  collation; int /*<<< orphan*/  consistentFmgrInfo; } ;
typedef  TYPE_1__* GinScanKey ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall8Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int*) ; 
 int /*<<< orphan*/  UInt16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
directBoolConsistentFn(GinScanKey key)
{
	/*
	 * Initialize recheckCurItem in case the consistentFn doesn't know it
	 * should set it.  The safe assumption in that case is to force recheck.
	 */
	key->recheckCurItem = true;

	return DatumGetBool(FunctionCall8Coll(key->consistentFmgrInfo,
										  key->collation,
										  PointerGetDatum(key->entryRes),
										  UInt16GetDatum(key->strategy),
										  key->query,
										  UInt32GetDatum(key->nuserentries),
										  PointerGetDatum(key->extra_data),
										  PointerGetDatum(&key->recheckCurItem),
										  PointerGetDatum(key->queryValues),
										  PointerGetDatum(key->queryCategories)));
}