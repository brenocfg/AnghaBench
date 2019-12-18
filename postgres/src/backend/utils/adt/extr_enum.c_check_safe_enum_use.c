#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_6__ {int /*<<< orphan*/  enumtypid; int /*<<< orphan*/  enumlabel; int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_data; } ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNSAFE_NEW_ENUM_VALUE_USAGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnumBlacklisted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleHeaderXminCommitted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_safe_enum_use(HeapTuple enumval_tup)
{
	TransactionId xmin;
	Form_pg_enum en = (Form_pg_enum) GETSTRUCT(enumval_tup);

	/*
	 * If the row is hinted as committed, it's surely safe.  This provides a
	 * fast path for all normal use-cases.
	 */
	if (HeapTupleHeaderXminCommitted(enumval_tup->t_data))
		return;

	/*
	 * Usually, a row would get hinted as committed when it's read or loaded
	 * into syscache; but just in case not, let's check the xmin directly.
	 */
	xmin = HeapTupleHeaderGetXmin(enumval_tup->t_data);
	if (!TransactionIdIsInProgress(xmin) &&
		TransactionIdDidCommit(xmin))
		return;

	/*
	 * Check if the enum value is blacklisted.  If not, it's safe, because it
	 * was made during CREATE TYPE AS ENUM and can't be shorter-lived than its
	 * owning type.  (This'd also be false for values made by other
	 * transactions; but the previous tests should have handled all of those.)
	 */
	if (!EnumBlacklisted(en->oid))
		return;

	/*
	 * There might well be other tests we could do here to narrow down the
	 * unsafe conditions, but for now just raise an exception.
	 */
	ereport(ERROR,
			(errcode(ERRCODE_UNSAFE_NEW_ENUM_VALUE_USAGE),
			 errmsg("unsafe use of new value \"%s\" of enum type %s",
					NameStr(en->enumlabel),
					format_type_be(en->enumtypid)),
			 errhint("New enum values must be committed before they can be used.")));
}