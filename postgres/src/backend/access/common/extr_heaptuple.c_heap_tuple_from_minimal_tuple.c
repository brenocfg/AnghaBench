#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_7__ {int t_len; scalar_t__ t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; } ;
struct TYPE_6__ {int t_len; } ;
typedef  TYPE_1__* MinimalTuple ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int HEAPTUPLESIZE ; 
 int /*<<< orphan*/  HeapTupleHeaderData ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int MINIMAL_TUPLE_OFFSET ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  t_infomask2 ; 

HeapTuple
heap_tuple_from_minimal_tuple(MinimalTuple mtup)
{
	HeapTuple	result;
	uint32		len = mtup->t_len + MINIMAL_TUPLE_OFFSET;

	result = (HeapTuple) palloc(HEAPTUPLESIZE + len);
	result->t_len = len;
	ItemPointerSetInvalid(&(result->t_self));
	result->t_tableOid = InvalidOid;
	result->t_data = (HeapTupleHeader) ((char *) result + HEAPTUPLESIZE);
	memcpy((char *) result->t_data + MINIMAL_TUPLE_OFFSET, mtup, mtup->t_len);
	memset(result->t_data, 0, offsetof(HeapTupleHeaderData, t_infomask2));
	return result;
}