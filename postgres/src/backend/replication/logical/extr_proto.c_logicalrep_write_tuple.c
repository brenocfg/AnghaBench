#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_18__ {int attlen; int /*<<< orphan*/  atttypid; scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_17__ {int /*<<< orphan*/  typoutput; } ;
struct TYPE_16__ {scalar_t__ t_len; } ;
struct TYPE_15__ {int natts; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int MaxTupleAttributeNumber ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_2__*) ; 
 TYPE_2__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL_ONDISK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enlargeStringInfo (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendcountedtext (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
logicalrep_write_tuple(StringInfo out, Relation rel, HeapTuple tuple)
{
	TupleDesc	desc;
	Datum		values[MaxTupleAttributeNumber];
	bool		isnull[MaxTupleAttributeNumber];
	int			i;
	uint16		nliveatts = 0;

	desc = RelationGetDescr(rel);

	for (i = 0; i < desc->natts; i++)
	{
		if (TupleDescAttr(desc, i)->attisdropped || TupleDescAttr(desc, i)->attgenerated)
			continue;
		nliveatts++;
	}
	pq_sendint16(out, nliveatts);

	/* try to allocate enough memory from the get-go */
	enlargeStringInfo(out, tuple->t_len +
					  nliveatts * (1 + 4));

	heap_deform_tuple(tuple, desc, values, isnull);

	/* Write the values */
	for (i = 0; i < desc->natts; i++)
	{
		HeapTuple	typtup;
		Form_pg_type typclass;
		Form_pg_attribute att = TupleDescAttr(desc, i);
		char	   *outputstr;

		if (att->attisdropped || att->attgenerated)
			continue;

		if (isnull[i])
		{
			pq_sendbyte(out, 'n');	/* null column */
			continue;
		}
		else if (att->attlen == -1 && VARATT_IS_EXTERNAL_ONDISK(values[i]))
		{
			pq_sendbyte(out, 'u');	/* unchanged toast column */
			continue;
		}

		typtup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(att->atttypid));
		if (!HeapTupleIsValid(typtup))
			elog(ERROR, "cache lookup failed for type %u", att->atttypid);
		typclass = (Form_pg_type) GETSTRUCT(typtup);

		pq_sendbyte(out, 't');	/* 'text' data follows */

		outputstr = OidOutputFunctionCall(typclass->typoutput, values[i]);
		pq_sendcountedtext(out, outputstr, strlen(outputstr), false);
		pfree(outputstr);

		ReleaseSysCache(typtup);
	}
}