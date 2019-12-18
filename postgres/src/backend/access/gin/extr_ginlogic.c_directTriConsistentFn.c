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
struct TYPE_3__ {int /*<<< orphan*/  queryCategories; int /*<<< orphan*/  queryValues; int /*<<< orphan*/  extra_data; int /*<<< orphan*/  nuserentries; int /*<<< orphan*/  query; int /*<<< orphan*/  strategy; int /*<<< orphan*/  entryRes; int /*<<< orphan*/  collation; int /*<<< orphan*/  triConsistentFmgrInfo; } ;
typedef  int /*<<< orphan*/  GinTernaryValue ;
typedef  TYPE_1__* GinScanKey ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetGinTernaryValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall7Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GinTernaryValue
directTriConsistentFn(GinScanKey key)
{
	return DatumGetGinTernaryValue(FunctionCall7Coll(
													 key->triConsistentFmgrInfo,
													 key->collation,
													 PointerGetDatum(key->entryRes),
													 UInt16GetDatum(key->strategy),
													 key->query,
													 UInt32GetDatum(key->nuserentries),
													 PointerGetDatum(key->extra_data),
													 PointerGetDatum(key->queryValues),
													 PointerGetDatum(key->queryCategories)));
}