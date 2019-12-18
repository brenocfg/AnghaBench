#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_6__ {scalar_t__ atttypid; } ;
struct TYPE_5__ {scalar_t__ natts; } ;

/* Variables and functions */
 scalar_t__ CONNECTBY_NCOLS ; 
 scalar_t__ CONNECTBY_NCOLS_NOBRANCH ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INT4OID ; 
 scalar_t__ TEXTOID ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 

__attribute__((used)) static void
validateConnectbyTupleDesc(TupleDesc td, bool show_branch, bool show_serial)
{
	int			serial_column = 0;

	if (show_serial)
		serial_column = 1;

	/* are there the correct number of columns */
	if (show_branch)
	{
		if (td->natts != (CONNECTBY_NCOLS + serial_column))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("invalid return type"),
					 errdetail("Query-specified return tuple has " \
							   "wrong number of columns.")));
	}
	else
	{
		if (td->natts != CONNECTBY_NCOLS_NOBRANCH + serial_column)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("invalid return type"),
					 errdetail("Query-specified return tuple has " \
							   "wrong number of columns.")));
	}

	/* check that the types of the first two columns match */
	if (TupleDescAttr(td, 0)->atttypid != TupleDescAttr(td, 1)->atttypid)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("invalid return type"),
				 errdetail("First two columns must be the same type.")));

	/* check that the type of the third column is INT4 */
	if (TupleDescAttr(td, 2)->atttypid != INT4OID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("invalid return type"),
				 errdetail("Third column must be type %s.",
						   format_type_be(INT4OID))));

	/* check that the type of the fourth column is TEXT if applicable */
	if (show_branch && TupleDescAttr(td, 3)->atttypid != TEXTOID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("invalid return type"),
				 errdetail("Fourth column must be type %s.",
						   format_type_be(TEXTOID))));

	/* check that the type of the fifth column is INT4 */
	if (show_branch && show_serial &&
		TupleDescAttr(td, 4)->atttypid != INT4OID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("query-specified return tuple not valid for Connectby: "
						"fifth column must be type %s",
						format_type_be(INT4OID))));

	/* check that the type of the fifth column is INT4 */
	if (!show_branch && show_serial &&
		TupleDescAttr(td, 3)->atttypid != INT4OID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("query-specified return tuple not valid for Connectby: "
						"fourth column must be type %s",
						format_type_be(INT4OID))));

	/* OK, the tupdesc is valid for our purposes */
}