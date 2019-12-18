#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
struct TYPE_5__ {int rdata_len; TYPE_2__* rdata_tail; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ registered_buffer ;
struct TYPE_6__ {char* data; int len; struct TYPE_6__* next; } ;
typedef  TYPE_2__ XLogRecData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  begininsert_called ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ max_rdatas ; 
 scalar_t__ num_rdatas ; 
 TYPE_2__* rdatas ; 
 TYPE_1__* registered_buffers ; 

void
XLogRegisterBufData(uint8 block_id, char *data, int len)
{
	registered_buffer *regbuf;
	XLogRecData *rdata;

	Assert(begininsert_called);

	/* find the registered buffer struct */
	regbuf = &registered_buffers[block_id];
	if (!regbuf->in_use)
		elog(ERROR, "no block with id %d registered with WAL insertion",
			 block_id);

	if (num_rdatas >= max_rdatas)
		elog(ERROR, "too much WAL data");
	rdata = &rdatas[num_rdatas++];

	rdata->data = data;
	rdata->len = len;

	regbuf->rdata_tail->next = rdata;
	regbuf->rdata_tail = rdata;
	regbuf->rdata_len += len;
}