#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_17__ {TYPE_10__* t_data; void* t_self; } ;
struct TYPE_16__ {void* new_tid; int /*<<< orphan*/  new_node; void* old_tid; int /*<<< orphan*/  old_node; } ;
struct TYPE_15__ {TYPE_2__* rs_new_rel; TYPE_1__* rs_old_rel; int /*<<< orphan*/  rs_logical_rewrite; int /*<<< orphan*/  rs_logical_xmin; } ;
struct TYPE_14__ {int /*<<< orphan*/  rd_node; } ;
struct TYPE_13__ {int /*<<< orphan*/  rd_node; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_infomask; } ;
typedef  TYPE_3__* RewriteState ;
typedef  TYPE_4__ LogicalRewriteMappingData ;
typedef  void* ItemPointerData ;
typedef  TYPE_5__* HeapTuple ;

/* Variables and functions */
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_10__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_10__*) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logical_rewrite_log_mapping (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
logical_rewrite_heap_tuple(RewriteState state, ItemPointerData old_tid,
						   HeapTuple new_tuple)
{
	ItemPointerData new_tid = new_tuple->t_self;
	TransactionId cutoff = state->rs_logical_xmin;
	TransactionId xmin;
	TransactionId xmax;
	bool		do_log_xmin = false;
	bool		do_log_xmax = false;
	LogicalRewriteMappingData map;

	/* no logical rewrite in progress, we don't need to log anything */
	if (!state->rs_logical_rewrite)
		return;

	xmin = HeapTupleHeaderGetXmin(new_tuple->t_data);
	/* use *GetUpdateXid to correctly deal with multixacts */
	xmax = HeapTupleHeaderGetUpdateXid(new_tuple->t_data);

	/*
	 * Log the mapping iff the tuple has been created recently.
	 */
	if (TransactionIdIsNormal(xmin) && !TransactionIdPrecedes(xmin, cutoff))
		do_log_xmin = true;

	if (!TransactionIdIsNormal(xmax))
	{
		/*
		 * no xmax is set, can't have any permanent ones, so this check is
		 * sufficient
		 */
	}
	else if (HEAP_XMAX_IS_LOCKED_ONLY(new_tuple->t_data->t_infomask))
	{
		/* only locked, we don't care */
	}
	else if (!TransactionIdPrecedes(xmax, cutoff))
	{
		/* tuple has been deleted recently, log */
		do_log_xmax = true;
	}

	/* if neither needs to be logged, we're done */
	if (!do_log_xmin && !do_log_xmax)
		return;

	/* fill out mapping information */
	map.old_node = state->rs_old_rel->rd_node;
	map.old_tid = old_tid;
	map.new_node = state->rs_new_rel->rd_node;
	map.new_tid = new_tid;

	/* ---
	 * Now persist the mapping for the individual xids that are affected. We
	 * need to log for both xmin and xmax if they aren't the same transaction
	 * since the mapping files are per "affected" xid.
	 * We don't muster all that much effort detecting whether xmin and xmax
	 * are actually the same transaction, we just check whether the xid is the
	 * same disregarding subtransactions. Logging too much is relatively
	 * harmless and we could never do the check fully since subtransaction
	 * data is thrown away during restarts.
	 * ---
	 */
	if (do_log_xmin)
		logical_rewrite_log_mapping(state, xmin, &map);
	/* separately log mapping for xmax unless it'd be redundant */
	if (do_log_xmax && !TransactionIdEquals(xmin, xmax))
		logical_rewrite_log_mapping(state, xmax, &map);
}