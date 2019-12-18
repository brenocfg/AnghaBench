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
struct TYPE_4__ {char* data; int len; struct TYPE_4__* next; } ;
typedef  TYPE_1__ XLogRecData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  begininsert_called ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mainrdata_last ; 
 int mainrdata_len ; 
 scalar_t__ max_rdatas ; 
 scalar_t__ num_rdatas ; 
 TYPE_1__* rdatas ; 

void
XLogRegisterData(char *data, int len)
{
	XLogRecData *rdata;

	Assert(begininsert_called);

	if (num_rdatas >= max_rdatas)
		elog(ERROR, "too much WAL data");
	rdata = &rdatas[num_rdatas++];

	rdata->data = data;
	rdata->len = len;

	/*
	 * we use the mainrdata_last pointer to track the end of the chain, so no
	 * need to clear 'next' here.
	 */

	mainrdata_last->next = rdata;
	mainrdata_last = rdata;

	mainrdata_len += len;
}