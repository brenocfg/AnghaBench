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
struct TYPE_3__ {int relpersistence; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
#define  RELPERSISTENCE_PERMANENT 129 
#define  RELPERSISTENCE_TEMP 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  isAnyTempNamespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isTempOrTempToastNamespace (int /*<<< orphan*/ ) ; 

void
RangeVarAdjustRelationPersistence(RangeVar *newRelation, Oid nspid)
{
	switch (newRelation->relpersistence)
	{
		case RELPERSISTENCE_TEMP:
			if (!isTempOrTempToastNamespace(nspid))
			{
				if (isAnyTempNamespace(nspid))
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
							 errmsg("cannot create relations in temporary schemas of other sessions")));
				else
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
							 errmsg("cannot create temporary relation in non-temporary schema")));
			}
			break;
		case RELPERSISTENCE_PERMANENT:
			if (isTempOrTempToastNamespace(nspid))
				newRelation->relpersistence = RELPERSISTENCE_TEMP;
			else if (isAnyTempNamespace(nspid))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
						 errmsg("cannot create relations in temporary schemas of other sessions")));
			break;
		default:
			if (isAnyTempNamespace(nspid))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
						 errmsg("only temporary relations may be created in temporary schemas")));
	}
}