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
struct TYPE_7__ {TYPE_3__* ps_ExprContext; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;
struct TYPE_10__ {int /*<<< orphan*/  bitmapqualorig; TYPE_2__ ss; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
typedef  TYPE_3__ ExprContext ;
typedef  TYPE_4__ BitmapHeapScanState ;

/* Variables and functions */
 int ExecQualAndReset (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static bool
BitmapHeapRecheck(BitmapHeapScanState *node, TupleTableSlot *slot)
{
	ExprContext *econtext;

	/*
	 * extract necessary information from index scan node
	 */
	econtext = node->ss.ps.ps_ExprContext;

	/* Does the tuple meet the original qual conditions? */
	econtext->ecxt_scantuple = slot;
	return ExecQualAndReset(node->bitmapqualorig, econtext);
}