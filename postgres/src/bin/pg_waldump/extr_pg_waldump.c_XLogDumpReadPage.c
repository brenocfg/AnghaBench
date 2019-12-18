#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_5__ {int /*<<< orphan*/  ws_dir; } ;
struct TYPE_6__ {TYPE_1__ segcxt; TYPE_3__* private_data; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_7__ {scalar_t__ endptr; int endptr_reached; int /*<<< orphan*/  timeline; } ;
typedef  TYPE_3__ XLogDumpPrivate ;

/* Variables and functions */
 scalar_t__ InvalidXLogRecPtr ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogDumpXLogRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

__attribute__((used)) static int
XLogDumpReadPage(XLogReaderState *state, XLogRecPtr targetPagePtr, int reqLen,
				 XLogRecPtr targetPtr, char *readBuff)
{
	XLogDumpPrivate *private = state->private_data;
	int			count = XLOG_BLCKSZ;

	if (private->endptr != InvalidXLogRecPtr)
	{
		if (targetPagePtr + XLOG_BLCKSZ <= private->endptr)
			count = XLOG_BLCKSZ;
		else if (targetPagePtr + reqLen <= private->endptr)
			count = private->endptr - targetPagePtr;
		else
		{
			private->endptr_reached = true;
			return -1;
		}
	}

	XLogDumpXLogRead(state->segcxt.ws_dir, private->timeline, targetPagePtr,
					 readBuff, count);

	return count;
}