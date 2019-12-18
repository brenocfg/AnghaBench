#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__** bd_info; TYPE_1__* bd_tupdesc; } ;
struct TYPE_12__ {TYPE_2__* bt_columns; int /*<<< orphan*/  bt_context; } ;
struct TYPE_11__ {int oi_nstored; } ;
struct TYPE_10__ {int bv_allnulls; int bv_hasnulls; int bv_attno; int /*<<< orphan*/ * bv_values; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BrinValues ;
typedef  TYPE_4__ BrinMemTuple ;
typedef  TYPE_5__ BrinDesc ;

/* Variables and functions */
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 

BrinMemTuple *
brin_memtuple_initialize(BrinMemTuple *dtuple, BrinDesc *brdesc)
{
	int			i;
	char	   *currdatum;

	MemoryContextReset(dtuple->bt_context);

	currdatum = (char *) dtuple +
		MAXALIGN(sizeof(BrinMemTuple) +
				 sizeof(BrinValues) * brdesc->bd_tupdesc->natts);
	for (i = 0; i < brdesc->bd_tupdesc->natts; i++)
	{
		dtuple->bt_columns[i].bv_allnulls = true;
		dtuple->bt_columns[i].bv_hasnulls = false;

		dtuple->bt_columns[i].bv_attno = i + 1;
		dtuple->bt_columns[i].bv_allnulls = true;
		dtuple->bt_columns[i].bv_hasnulls = false;
		dtuple->bt_columns[i].bv_values = (Datum *) currdatum;
		currdatum += sizeof(Datum) * brdesc->bd_info[i]->oi_nstored;
	}

	return dtuple;
}