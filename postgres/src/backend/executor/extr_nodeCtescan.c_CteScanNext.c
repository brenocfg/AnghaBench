#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {TYPE_4__* state; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/  readptr; TYPE_3__* leader; int /*<<< orphan*/  cteplanstate; TYPE_2__ ss; } ;
struct TYPE_10__ {int /*<<< orphan*/  es_direction; } ;
struct TYPE_9__ {int eof_cte; int /*<<< orphan*/ * cte_table; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_4__ EState ;
typedef  TYPE_5__ CteScanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecCopySlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 
 int ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_advance (int /*<<< orphan*/ *,int) ; 
 int tuplestore_ateof (int /*<<< orphan*/ *) ; 
 scalar_t__ tuplestore_gettupleslot (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttupleslot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
CteScanNext(CteScanState *node)
{
	EState	   *estate;
	ScanDirection dir;
	bool		forward;
	Tuplestorestate *tuplestorestate;
	bool		eof_tuplestore;
	TupleTableSlot *slot;

	/*
	 * get state info from node
	 */
	estate = node->ss.ps.state;
	dir = estate->es_direction;
	forward = ScanDirectionIsForward(dir);
	tuplestorestate = node->leader->cte_table;
	tuplestore_select_read_pointer(tuplestorestate, node->readptr);
	slot = node->ss.ss_ScanTupleSlot;

	/*
	 * If we are not at the end of the tuplestore, or are going backwards, try
	 * to fetch a tuple from tuplestore.
	 */
	eof_tuplestore = tuplestore_ateof(tuplestorestate);

	if (!forward && eof_tuplestore)
	{
		if (!node->leader->eof_cte)
		{
			/*
			 * When reversing direction at tuplestore EOF, the first
			 * gettupleslot call will fetch the last-added tuple; but we want
			 * to return the one before that, if possible. So do an extra
			 * fetch.
			 */
			if (!tuplestore_advance(tuplestorestate, forward))
				return NULL;	/* the tuplestore must be empty */
		}
		eof_tuplestore = false;
	}

	/*
	 * If we can fetch another tuple from the tuplestore, return it.
	 *
	 * Note: we have to use copy=true in the tuplestore_gettupleslot call,
	 * because we are sharing the tuplestore with other nodes that might write
	 * into the tuplestore before we get called again.
	 */
	if (!eof_tuplestore)
	{
		if (tuplestore_gettupleslot(tuplestorestate, forward, true, slot))
			return slot;
		if (forward)
			eof_tuplestore = true;
	}

	/*
	 * If necessary, try to fetch another row from the CTE query.
	 *
	 * Note: the eof_cte state variable exists to short-circuit further calls
	 * of the CTE plan.  It's not optional, unfortunately, because some plan
	 * node types are not robust about being called again when they've already
	 * returned NULL.
	 */
	if (eof_tuplestore && !node->leader->eof_cte)
	{
		TupleTableSlot *cteslot;

		/*
		 * We can only get here with forward==true, so no need to worry about
		 * which direction the subplan will go.
		 */
		cteslot = ExecProcNode(node->cteplanstate);
		if (TupIsNull(cteslot))
		{
			node->leader->eof_cte = true;
			return NULL;
		}

		/*
		 * There are corner cases where the subplan could change which
		 * tuplestore read pointer is active, so be sure to reselect ours
		 * before storing the tuple we got.
		 */
		tuplestore_select_read_pointer(tuplestorestate, node->readptr);

		/*
		 * Append a copy of the returned tuple to tuplestore.  NOTE: because
		 * our read pointer is certainly in EOF state, its read position will
		 * move forward over the added tuple.  This is what we want.  Also,
		 * any other readers will *not* move past the new tuple, which is what
		 * they want.
		 */
		tuplestore_puttupleslot(tuplestorestate, cteslot);

		/*
		 * We MUST copy the CTE query's output tuple into our own slot. This
		 * is because other CteScan nodes might advance the CTE query before
		 * we are called again, and our output tuple must stay stable over
		 * that.
		 */
		return ExecCopySlot(slot, cteslot);
	}

	/*
	 * Nothing left ...
	 */
	return ExecClearTuple(slot);
}