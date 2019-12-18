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
typedef  int uint64 ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_7__ {scalar_t__ pageno; } ;
struct TYPE_6__ {int offset; int flags; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__ LargeObjectDesc ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_largeobject ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_largeobject_loid ; 
 int /*<<< orphan*/  Anum_pg_largeobject_pageno ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterEqualStrategyNumber ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4GE ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleHasNulls (int /*<<< orphan*/ *) ; 
 int IFS_RDLOCK ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int LOBLKSIZE ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VARDATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getdatafield (TYPE_2__*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  lo_heap_r ; 
 int /*<<< orphan*/  lo_index_r ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 
 int /*<<< orphan*/  open_lo_relation () ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_beginscan_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
inv_read(LargeObjectDesc *obj_desc, char *buf, int nbytes)
{
	int			nread = 0;
	int64		n;
	int64		off;
	int			len;
	int32		pageno = (int32) (obj_desc->offset / LOBLKSIZE);
	uint64		pageoff;
	ScanKeyData skey[2];
	SysScanDesc sd;
	HeapTuple	tuple;

	Assert(PointerIsValid(obj_desc));
	Assert(buf != NULL);

	if ((obj_desc->flags & IFS_RDLOCK) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied for large object %u",
						obj_desc->id)));

	if (nbytes <= 0)
		return 0;

	open_lo_relation();

	ScanKeyInit(&skey[0],
				Anum_pg_largeobject_loid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(obj_desc->id));

	ScanKeyInit(&skey[1],
				Anum_pg_largeobject_pageno,
				BTGreaterEqualStrategyNumber, F_INT4GE,
				Int32GetDatum(pageno));

	sd = systable_beginscan_ordered(lo_heap_r, lo_index_r,
									obj_desc->snapshot, 2, skey);

	while ((tuple = systable_getnext_ordered(sd, ForwardScanDirection)) != NULL)
	{
		Form_pg_largeobject data;
		bytea	   *datafield;
		bool		pfreeit;

		if (HeapTupleHasNulls(tuple))	/* paranoia */
			elog(ERROR, "null field found in pg_largeobject");
		data = (Form_pg_largeobject) GETSTRUCT(tuple);

		/*
		 * We expect the indexscan will deliver pages in order.  However,
		 * there may be missing pages if the LO contains unwritten "holes". We
		 * want missing sections to read out as zeroes.
		 */
		pageoff = ((uint64) data->pageno) * LOBLKSIZE;
		if (pageoff > obj_desc->offset)
		{
			n = pageoff - obj_desc->offset;
			n = (n <= (nbytes - nread)) ? n : (nbytes - nread);
			MemSet(buf + nread, 0, n);
			nread += n;
			obj_desc->offset += n;
		}

		if (nread < nbytes)
		{
			Assert(obj_desc->offset >= pageoff);
			off = (int) (obj_desc->offset - pageoff);
			Assert(off >= 0 && off < LOBLKSIZE);

			getdatafield(data, &datafield, &len, &pfreeit);
			if (len > off)
			{
				n = len - off;
				n = (n <= (nbytes - nread)) ? n : (nbytes - nread);
				memcpy(buf + nread, VARDATA(datafield) + off, n);
				nread += n;
				obj_desc->offset += n;
			}
			if (pfreeit)
				pfree(datafield);
		}

		if (nread >= nbytes)
			break;
	}

	systable_endscan_ordered(sd);

	return nread;
}