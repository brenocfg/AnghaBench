#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  indexed_tlist ;
struct TYPE_5__ {int /*<<< orphan*/ * qual; int /*<<< orphan*/ * targetlist; } ;
struct TYPE_6__ {scalar_t__ scanrelid; TYPE_1__ plan; } ;
struct TYPE_7__ {scalar_t__ fdw_scan_tlist; int /*<<< orphan*/ * fs_relids; int /*<<< orphan*/ * fdw_recheck_quals; int /*<<< orphan*/ * fdw_exprs; TYPE_2__ scan; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ ForeignScan ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_VAR ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * build_tlist_index (scalar_t__) ; 
 void* fix_scan_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fix_upper_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_foreignscan_references(PlannerInfo *root,
						   ForeignScan *fscan,
						   int rtoffset)
{
	/* Adjust scanrelid if it's valid */
	if (fscan->scan.scanrelid > 0)
		fscan->scan.scanrelid += rtoffset;

	if (fscan->fdw_scan_tlist != NIL || fscan->scan.scanrelid == 0)
	{
		/*
		 * Adjust tlist, qual, fdw_exprs, fdw_recheck_quals to reference
		 * foreign scan tuple
		 */
		indexed_tlist *itlist = build_tlist_index(fscan->fdw_scan_tlist);

		fscan->scan.plan.targetlist = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->scan.plan.targetlist,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		fscan->scan.plan.qual = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->scan.plan.qual,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		fscan->fdw_exprs = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->fdw_exprs,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		fscan->fdw_recheck_quals = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->fdw_recheck_quals,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		pfree(itlist);
		/* fdw_scan_tlist itself just needs fix_scan_list() adjustments */
		fscan->fdw_scan_tlist =
			fix_scan_list(root, fscan->fdw_scan_tlist, rtoffset);
	}
	else
	{
		/*
		 * Adjust tlist, qual, fdw_exprs, fdw_recheck_quals in the standard
		 * way
		 */
		fscan->scan.plan.targetlist =
			fix_scan_list(root, fscan->scan.plan.targetlist, rtoffset);
		fscan->scan.plan.qual =
			fix_scan_list(root, fscan->scan.plan.qual, rtoffset);
		fscan->fdw_exprs =
			fix_scan_list(root, fscan->fdw_exprs, rtoffset);
		fscan->fdw_recheck_quals =
			fix_scan_list(root, fscan->fdw_recheck_quals, rtoffset);
	}

	/* Adjust fs_relids if needed */
	if (rtoffset > 0)
	{
		Bitmapset  *tempset = NULL;
		int			x = -1;

		while ((x = bms_next_member(fscan->fs_relids, x)) >= 0)
			tempset = bms_add_member(tempset, x + rtoffset);
		fscan->fs_relids = tempset;
	}
}