#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_10__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_7__ {TYPE_4__* ps_ExprContext; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;
struct TYPE_9__ {int /*<<< orphan*/  indexqualorig; TYPE_2__ ss; } ;
typedef  TYPE_3__ IndexScanState ;
typedef  TYPE_4__ ExprContext ;

/* Variables and functions */
 int ExecQualAndReset (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static bool
IndexRecheck(IndexScanState *node, TupleTableSlot *slot)
{
	ExprContext *econtext;

	/*
	 * extract necessary information from index scan node
	 */
	econtext = node->ss.ps.ps_ExprContext;

	/* Does the tuple meet the indexqual condition? */
	econtext->ecxt_scantuple = slot;
	return ExecQualAndReset(node->indexqualorig, econtext);
}