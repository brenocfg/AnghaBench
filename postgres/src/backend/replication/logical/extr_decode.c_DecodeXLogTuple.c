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
struct TYPE_8__ {int /*<<< orphan*/  t_hoff; int /*<<< orphan*/  t_infomask2; int /*<<< orphan*/  t_infomask; } ;
typedef  TYPE_2__ xl_heap_header ;
struct TYPE_10__ {int /*<<< orphan*/  t_hoff; int /*<<< orphan*/  t_infomask2; int /*<<< orphan*/  t_infomask; } ;
struct TYPE_7__ {int t_len; TYPE_4__* t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {TYPE_1__ tuple; } ;
typedef  int Size ;
typedef  TYPE_3__ ReorderBufferTupleBuf ;
typedef  TYPE_4__* HeapTupleHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int SizeOfHeapHeader ; 
 int SizeofHeapTupleHeader ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
DecodeXLogTuple(char *data, Size len, ReorderBufferTupleBuf *tuple)
{
	xl_heap_header xlhdr;
	int			datalen = len - SizeOfHeapHeader;
	HeapTupleHeader header;

	Assert(datalen >= 0);

	tuple->tuple.t_len = datalen + SizeofHeapTupleHeader;
	header = tuple->tuple.t_data;

	/* not a disk based tuple */
	ItemPointerSetInvalid(&tuple->tuple.t_self);

	/* we can only figure this out after reassembling the transactions */
	tuple->tuple.t_tableOid = InvalidOid;

	/* data is not stored aligned, copy to aligned storage */
	memcpy((char *) &xlhdr,
		   data,
		   SizeOfHeapHeader);

	memset(header, 0, SizeofHeapTupleHeader);

	memcpy(((char *) tuple->tuple.t_data) + SizeofHeapTupleHeader,
		   data + SizeOfHeapHeader,
		   datalen);

	header->t_infomask = xlhdr.t_infomask;
	header->t_infomask2 = xlhdr.t_infomask2;
	header->t_hoff = xlhdr.t_hoff;
}