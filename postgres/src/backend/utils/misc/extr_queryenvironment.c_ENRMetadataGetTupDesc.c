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
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_7__ {scalar_t__ reliddesc; int /*<<< orphan*/ * tupdesc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__* EphemeralNamedRelationMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (scalar_t__,int /*<<< orphan*/ ) ; 

TupleDesc
ENRMetadataGetTupDesc(EphemeralNamedRelationMetadata enrmd)
{
	TupleDesc	tupdesc;

	/* One, and only one, of these fields must be filled. */
	Assert((enrmd->reliddesc == InvalidOid) != (enrmd->tupdesc == NULL));

	if (enrmd->tupdesc != NULL)
		tupdesc = enrmd->tupdesc;
	else
	{
		Relation	relation;

		relation = table_open(enrmd->reliddesc, NoLock);
		tupdesc = relation->rd_att;
		table_close(relation, NoLock);
	}

	return tupdesc;
}