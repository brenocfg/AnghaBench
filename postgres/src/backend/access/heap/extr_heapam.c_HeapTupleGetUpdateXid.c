#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  t_infomask; } ;
typedef  TYPE_1__* HeapTupleHeader ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmax (TYPE_1__*) ; 
 int /*<<< orphan*/  MultiXactIdGetUpdateXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TransactionId
HeapTupleGetUpdateXid(HeapTupleHeader tuple)
{
	return MultiXactIdGetUpdateXid(HeapTupleHeaderGetRawXmax(tuple),
								   tuple->t_infomask);
}