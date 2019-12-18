#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int TM_Result ;
typedef  int /*<<< orphan*/  TM_FailureData ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
#define  TM_Deleted 131 
#define  TM_Ok 130 
#define  TM_SelfModified 129 
#define  TM_Updated 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int table_tuple_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

void
simple_table_tuple_delete(Relation rel, ItemPointer tid, Snapshot snapshot)
{
	TM_Result	result;
	TM_FailureData tmfd;

	result = table_tuple_delete(rel, tid,
								GetCurrentCommandId(true),
								snapshot, InvalidSnapshot,
								true /* wait for commit */ ,
								&tmfd, false /* changingPart */ );

	switch (result)
	{
		case TM_SelfModified:
			/* Tuple was already updated in current command? */
			elog(ERROR, "tuple already updated by self");
			break;

		case TM_Ok:
			/* done successfully */
			break;

		case TM_Updated:
			elog(ERROR, "tuple concurrently updated");
			break;

		case TM_Deleted:
			elog(ERROR, "tuple concurrently deleted");
			break;

		default:
			elog(ERROR, "unrecognized table_tuple_delete status: %u", result);
			break;
	}
}