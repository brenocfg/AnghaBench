#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_8__ {TYPE_1__* rd_indam; } ;
struct TYPE_7__ {int kill_prior_tuple; TYPE_4__* indexRelation; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* amgetbitmap ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  TYPE_2__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SCAN_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CHECKS ; 
 int /*<<< orphan*/  amgetbitmap ; 
 int /*<<< orphan*/  pgstat_count_index_tuples (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

int64
index_getbitmap(IndexScanDesc scan, TIDBitmap *bitmap)
{
	int64		ntids;

	SCAN_CHECKS;
	CHECK_SCAN_PROCEDURE(amgetbitmap);

	/* just make sure this is false... */
	scan->kill_prior_tuple = false;

	/*
	 * have the am's getbitmap proc do all the work.
	 */
	ntids = scan->indexRelation->rd_indam->amgetbitmap(scan, bitmap);

	pgstat_count_index_tuples(scan->indexRelation, ntids);

	return ntids;
}