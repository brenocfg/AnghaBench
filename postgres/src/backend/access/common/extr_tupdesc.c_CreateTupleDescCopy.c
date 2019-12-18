#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_11__ {int attnotnull; int atthasdef; int atthasmissing; char attidentity; char attgenerated; } ;
struct TYPE_10__ {int natts; int /*<<< orphan*/  tdtypmod; int /*<<< orphan*/  tdtypeid; } ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  FormData_pg_attribute ;

/* Variables and functions */
 TYPE_1__* CreateTemplateTupleDesc (int) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

TupleDesc
CreateTupleDescCopy(TupleDesc tupdesc)
{
	TupleDesc	desc;
	int			i;

	desc = CreateTemplateTupleDesc(tupdesc->natts);

	/* Flat-copy the attribute array */
	memcpy(TupleDescAttr(desc, 0),
		   TupleDescAttr(tupdesc, 0),
		   desc->natts * sizeof(FormData_pg_attribute));

	/*
	 * Since we're not copying constraints and defaults, clear fields
	 * associated with them.
	 */
	for (i = 0; i < desc->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(desc, i);

		att->attnotnull = false;
		att->atthasdef = false;
		att->atthasmissing = false;
		att->attidentity = '\0';
		att->attgenerated = '\0';
	}

	/* We can copy the tuple type identification, too */
	desc->tdtypeid = tupdesc->tdtypeid;
	desc->tdtypmod = tupdesc->tdtypmod;

	return desc;
}