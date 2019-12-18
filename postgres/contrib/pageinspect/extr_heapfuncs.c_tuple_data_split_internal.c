#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  bits8 ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_14__ {int attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {int natts; } ;
struct TYPE_11__ {scalar_t__ relam; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayBuildState ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BYTEAOID ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/ * DatumGetByteaPCopy (char*) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int HEAP_HASNULL ; 
 int HEAP_NATTS_MASK ; 
 scalar_t__ HEAP_TABLE_AM_OID ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (char*) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_INDIRECT (char*) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_ONDISK (char*) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int VARSIZE_ANY (char*) ; 
 int /*<<< orphan*/ * accumArrayResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int att_addlength_pointer (int,int,char*) ; 
 int att_align_nominal (int,int /*<<< orphan*/ ) ; 
 int att_align_pointer (int,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ att_isnull (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * initArrayResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeArrayResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
tuple_data_split_internal(Oid relid, char *tupdata,
						  uint16 tupdata_len, uint16 t_infomask,
						  uint16 t_infomask2, bits8 *t_bits,
						  bool do_detoast)
{
	ArrayBuildState *raw_attrs;
	int			nattrs;
	int			i;
	int			off = 0;
	Relation	rel;
	TupleDesc	tupdesc;

	/* Get tuple descriptor from relation OID */
	rel = relation_open(relid, AccessShareLock);
	tupdesc = RelationGetDescr(rel);

	raw_attrs = initArrayResult(BYTEAOID, CurrentMemoryContext, false);
	nattrs = tupdesc->natts;

	if (rel->rd_rel->relam != HEAP_TABLE_AM_OID)
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("only heap AM is supported")));

	if (nattrs < (t_infomask2 & HEAP_NATTS_MASK))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("number of attributes in tuple header is greater than number of attributes in tuple descriptor")));

	for (i = 0; i < nattrs; i++)
	{
		Form_pg_attribute attr;
		bool		is_null;
		bytea	   *attr_data = NULL;

		attr = TupleDescAttr(tupdesc, i);

		/*
		 * Tuple header can specify less attributes than tuple descriptor as
		 * ALTER TABLE ADD COLUMN without DEFAULT keyword does not actually
		 * change tuples in pages, so attributes with numbers greater than
		 * (t_infomask2 & HEAP_NATTS_MASK) should be treated as NULL.
		 */
		if (i >= (t_infomask2 & HEAP_NATTS_MASK))
			is_null = true;
		else
			is_null = (t_infomask & HEAP_HASNULL) && att_isnull(i, t_bits);

		if (!is_null)
		{
			int			len;

			if (attr->attlen == -1)
			{
				off = att_align_pointer(off, attr->attalign, -1,
										tupdata + off);

				/*
				 * As VARSIZE_ANY throws an exception if it can't properly
				 * detect the type of external storage in macros VARTAG_SIZE,
				 * this check is repeated to have a nicer error handling.
				 */
				if (VARATT_IS_EXTERNAL(tupdata + off) &&
					!VARATT_IS_EXTERNAL_ONDISK(tupdata + off) &&
					!VARATT_IS_EXTERNAL_INDIRECT(tupdata + off))
					ereport(ERROR,
							(errcode(ERRCODE_DATA_CORRUPTED),
							 errmsg("first byte of varlena attribute is incorrect for attribute %d", i)));

				len = VARSIZE_ANY(tupdata + off);
			}
			else
			{
				off = att_align_nominal(off, attr->attalign);
				len = attr->attlen;
			}

			if (tupdata_len < off + len)
				ereport(ERROR,
						(errcode(ERRCODE_DATA_CORRUPTED),
						 errmsg("unexpected end of tuple data")));

			if (attr->attlen == -1 && do_detoast)
				attr_data = DatumGetByteaPCopy(tupdata + off);
			else
			{
				attr_data = (bytea *) palloc(len + VARHDRSZ);
				SET_VARSIZE(attr_data, len + VARHDRSZ);
				memcpy(VARDATA(attr_data), tupdata + off, len);
			}

			off = att_addlength_pointer(off, attr->attlen,
										tupdata + off);
		}

		raw_attrs = accumArrayResult(raw_attrs, PointerGetDatum(attr_data),
									 is_null, BYTEAOID, CurrentMemoryContext);
		if (attr_data)
			pfree(attr_data);
	}

	if (tupdata_len != off)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("end of tuple reached without looking at all its data")));

	relation_close(rel, AccessShareLock);

	return makeArrayResult(raw_attrs, CurrentMemoryContext);
}