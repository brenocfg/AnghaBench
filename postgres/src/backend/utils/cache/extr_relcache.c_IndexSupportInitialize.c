#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ oidvector ;
struct TYPE_6__ {int /*<<< orphan*/  supportProcs; int /*<<< orphan*/  opcintype; int /*<<< orphan*/  opcfamily; } ;
typedef  int StrategyNumber ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  TYPE_2__ OpClassCacheEnt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* LookupOpclassInfo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
IndexSupportInitialize(oidvector *indclass,
					   RegProcedure *indexSupport,
					   Oid *opFamily,
					   Oid *opcInType,
					   StrategyNumber maxSupportNumber,
					   AttrNumber maxAttributeNumber)
{
	int			attIndex;

	for (attIndex = 0; attIndex < maxAttributeNumber; attIndex++)
	{
		OpClassCacheEnt *opcentry;

		if (!OidIsValid(indclass->values[attIndex]))
			elog(ERROR, "bogus pg_index tuple");

		/* look up the info for this opclass, using a cache */
		opcentry = LookupOpclassInfo(indclass->values[attIndex],
									 maxSupportNumber);

		/* copy cached data into relcache entry */
		opFamily[attIndex] = opcentry->opcfamily;
		opcInType[attIndex] = opcentry->opcintype;
		if (maxSupportNumber > 0)
			memcpy(&indexSupport[attIndex * maxSupportNumber],
				   opcentry->supportProcs,
				   maxSupportNumber * sizeof(RegProcedure));
	}
}