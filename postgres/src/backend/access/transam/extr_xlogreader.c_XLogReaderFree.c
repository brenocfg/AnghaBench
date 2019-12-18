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
struct TYPE_6__ {struct TYPE_6__* readBuf; struct TYPE_6__* readRecordBuf; struct TYPE_6__* errormsg_buf; struct TYPE_6__* main_data; TYPE_1__* blocks; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_5__ {TYPE_2__* data; } ;

/* Variables and functions */
 int XLR_MAX_BLOCK_ID ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

void
XLogReaderFree(XLogReaderState *state)
{
	int			block_id;

	for (block_id = 0; block_id <= XLR_MAX_BLOCK_ID; block_id++)
	{
		if (state->blocks[block_id].data)
			pfree(state->blocks[block_id].data);
	}
	if (state->main_data)
		pfree(state->main_data);

	pfree(state->errormsg_buf);
	if (state->readRecordBuf)
		pfree(state->readRecordBuf);
	pfree(state->readBuf);
	pfree(state);
}