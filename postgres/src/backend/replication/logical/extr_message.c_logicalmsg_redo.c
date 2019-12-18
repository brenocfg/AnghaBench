#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ XLOG_LOGICAL_MESSAGE ; 
 scalar_t__ XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
logicalmsg_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info != XLOG_LOGICAL_MESSAGE)
		elog(PANIC, "logicalmsg_redo: unknown op code %u", info);

	/* This is only interesting for logical decoding, see decode.c. */
}