#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
typedef  scalar_t__ int16 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {scalar_t__ resorigcol; scalar_t__ resorigtbl; scalar_t__ resjunk; } ;
typedef  TYPE_2__ TargetEntry ;
struct TYPE_9__ {scalar_t__ attlen; int /*<<< orphan*/  attname; scalar_t__ atttypmod; scalar_t__ atttypid; } ;
struct TYPE_7__ {int natts; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int MAX_CONVERSION_GROWTH ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  enlargeStringInfo (int /*<<< orphan*/ ,int) ; 
 scalar_t__ getBaseTypeAndTypmod (scalar_t__,scalar_t__*) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_writeint16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_writeint32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_writestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SendRowDescriptionCols_3(StringInfo buf, TupleDesc typeinfo, List *targetlist, int16 *formats)
{
	int			natts = typeinfo->natts;
	int			i;
	ListCell   *tlist_item = list_head(targetlist);

	/*
	 * Preallocate memory for the entire message to be sent. That allows to
	 * use the significantly faster inline pqformat.h functions and to avoid
	 * reallocations.
	 *
	 * Have to overestimate the size of the column-names, to account for
	 * character set overhead.
	 */
	enlargeStringInfo(buf, (NAMEDATALEN * MAX_CONVERSION_GROWTH /* attname */
							+ sizeof(Oid)	/* resorigtbl */
							+ sizeof(AttrNumber)	/* resorigcol */
							+ sizeof(Oid)	/* atttypid */
							+ sizeof(int16) /* attlen */
							+ sizeof(int32) /* attypmod */
							+ sizeof(int16) /* format */
							) * natts);

	for (i = 0; i < natts; ++i)
	{
		Form_pg_attribute att = TupleDescAttr(typeinfo, i);
		Oid			atttypid = att->atttypid;
		int32		atttypmod = att->atttypmod;
		Oid			resorigtbl;
		AttrNumber	resorigcol;
		int16		format;

		/*
		 * If column is a domain, send the base type and typmod instead.
		 * Lookup before sending any ints, for efficiency.
		 */
		atttypid = getBaseTypeAndTypmod(atttypid, &atttypmod);

		/* Do we have a non-resjunk tlist item? */
		while (tlist_item &&
			   ((TargetEntry *) lfirst(tlist_item))->resjunk)
			tlist_item = lnext(targetlist, tlist_item);
		if (tlist_item)
		{
			TargetEntry *tle = (TargetEntry *) lfirst(tlist_item);

			resorigtbl = tle->resorigtbl;
			resorigcol = tle->resorigcol;
			tlist_item = lnext(targetlist, tlist_item);
		}
		else
		{
			/* No info available, so send zeroes */
			resorigtbl = 0;
			resorigcol = 0;
		}

		if (formats)
			format = formats[i];
		else
			format = 0;

		pq_writestring(buf, NameStr(att->attname));
		pq_writeint32(buf, resorigtbl);
		pq_writeint16(buf, resorigcol);
		pq_writeint32(buf, atttypid);
		pq_writeint16(buf, att->attlen);
		pq_writeint32(buf, atttypmod);
		pq_writeint16(buf, format);
	}
}