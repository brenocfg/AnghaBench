#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {scalar_t__ attlen; scalar_t__ attalign; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attisdropped; } ;
struct TYPE_7__ {int natts; } ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsBinaryCoercible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int,...) ; 
 int /*<<< orphan*/  errdetail_plural (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tupledesc_match(TupleDesc dst_tupdesc, TupleDesc src_tupdesc)
{
	int			i;

	if (dst_tupdesc->natts != src_tupdesc->natts)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("function return row and query-specified return row do not match"),
				 errdetail_plural("Returned row contains %d attribute, but query expects %d.",
								  "Returned row contains %d attributes, but query expects %d.",
								  src_tupdesc->natts,
								  src_tupdesc->natts, dst_tupdesc->natts)));

	for (i = 0; i < dst_tupdesc->natts; i++)
	{
		Form_pg_attribute dattr = TupleDescAttr(dst_tupdesc, i);
		Form_pg_attribute sattr = TupleDescAttr(src_tupdesc, i);

		if (IsBinaryCoercible(sattr->atttypid, dattr->atttypid))
			continue;			/* no worries */
		if (!dattr->attisdropped)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("function return row and query-specified return row do not match"),
					 errdetail("Returned type %s at ordinal position %d, but query expects %s.",
							   format_type_be(sattr->atttypid),
							   i + 1,
							   format_type_be(dattr->atttypid))));

		if (dattr->attlen != sattr->attlen ||
			dattr->attalign != sattr->attalign)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("function return row and query-specified return row do not match"),
					 errdetail("Physical storage mismatch on dropped attribute at ordinal position %d.",
							   i + 1)));
	}
}