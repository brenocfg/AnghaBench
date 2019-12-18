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
struct TYPE_7__ {int frzflags; int /*<<< orphan*/  t_infomask2; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  xmax; } ;
typedef  TYPE_1__ xl_heap_freeze_tuple ;
struct TYPE_8__ {int /*<<< orphan*/  t_infomask2; int /*<<< orphan*/  t_infomask; } ;
typedef  TYPE_2__* HeapTupleHeader ;

/* Variables and functions */
 int /*<<< orphan*/  FrozenTransactionId ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXvac (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int XLH_FREEZE_XVAC ; 
 int XLH_INVALID_XVAC ; 

void
heap_execute_freeze_tuple(HeapTupleHeader tuple, xl_heap_freeze_tuple *frz)
{
	HeapTupleHeaderSetXmax(tuple, frz->xmax);

	if (frz->frzflags & XLH_FREEZE_XVAC)
		HeapTupleHeaderSetXvac(tuple, FrozenTransactionId);

	if (frz->frzflags & XLH_INVALID_XVAC)
		HeapTupleHeaderSetXvac(tuple, InvalidTransactionId);

	tuple->t_infomask = frz->t_infomask;
	tuple->t_infomask2 = frz->t_infomask2;
}