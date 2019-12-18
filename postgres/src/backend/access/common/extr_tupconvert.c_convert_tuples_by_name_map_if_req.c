#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_10__ {scalar_t__ attlen; scalar_t__ attalign; scalar_t__ attisdropped; } ;
struct TYPE_9__ {int natts; } ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int* convert_tuples_by_name_map (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (int*) ; 

AttrNumber *
convert_tuples_by_name_map_if_req(TupleDesc indesc,
								  TupleDesc outdesc)
{
	AttrNumber *attrMap;
	int			n = outdesc->natts;
	int			i;
	bool		same;

	/* Verify compatibility and prepare attribute-number map */
	attrMap = convert_tuples_by_name_map(indesc, outdesc);

	/*
	 * Check to see if the map is one-to-one, in which case we need not do a
	 * tuple conversion.
	 */
	if (indesc->natts == outdesc->natts)
	{
		same = true;
		for (i = 0; i < n; i++)
		{
			Form_pg_attribute inatt;
			Form_pg_attribute outatt;

			if (attrMap[i] == (i + 1))
				continue;

			/*
			 * If it's a dropped column and the corresponding input column is
			 * also dropped, we needn't convert.  However, attlen and attalign
			 * must agree.
			 */
			inatt = TupleDescAttr(indesc, i);
			outatt = TupleDescAttr(outdesc, i);
			if (attrMap[i] == 0 &&
				inatt->attisdropped &&
				inatt->attlen == outatt->attlen &&
				inatt->attalign == outatt->attalign)
				continue;

			same = false;
			break;
		}
	}
	else
		same = false;

	if (same)
	{
		/* Runtime conversion is not needed */
		pfree(attrMap);
		return NULL;
	}
	else
		return attrMap;
}