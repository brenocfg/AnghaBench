#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ searchMode; int attnum; int /*<<< orphan*/  triConsistentFn; int /*<<< orphan*/  boolConsistentFn; int /*<<< orphan*/  collation; TYPE_2__* triConsistentFmgrInfo; TYPE_1__* consistentFmgrInfo; } ;
struct TYPE_9__ {TYPE_2__* triConsistentFn; TYPE_1__* consistentFn; int /*<<< orphan*/ * supportCollation; } ;
struct TYPE_8__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  fn_oid; } ;
typedef  TYPE_3__ GinState ;
typedef  TYPE_4__* GinScanKey ;

/* Variables and functions */
 scalar_t__ GIN_SEARCH_MODE_EVERYTHING ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  directBoolConsistentFn ; 
 int /*<<< orphan*/  directTriConsistentFn ; 
 int /*<<< orphan*/  shimBoolConsistentFn ; 
 int /*<<< orphan*/  shimTriConsistentFn ; 
 int /*<<< orphan*/  trueConsistentFn ; 
 int /*<<< orphan*/  trueTriConsistentFn ; 

void
ginInitConsistentFunction(GinState *ginstate, GinScanKey key)
{
	if (key->searchMode == GIN_SEARCH_MODE_EVERYTHING)
	{
		key->boolConsistentFn = trueConsistentFn;
		key->triConsistentFn = trueTriConsistentFn;
	}
	else
	{
		key->consistentFmgrInfo = &ginstate->consistentFn[key->attnum - 1];
		key->triConsistentFmgrInfo = &ginstate->triConsistentFn[key->attnum - 1];
		key->collation = ginstate->supportCollation[key->attnum - 1];

		if (OidIsValid(ginstate->consistentFn[key->attnum - 1].fn_oid))
			key->boolConsistentFn = directBoolConsistentFn;
		else
			key->boolConsistentFn = shimBoolConsistentFn;

		if (OidIsValid(ginstate->triConsistentFn[key->attnum - 1].fn_oid))
			key->triConsistentFn = directTriConsistentFn;
		else
			key->triConsistentFn = shimTriConsistentFn;
	}
}