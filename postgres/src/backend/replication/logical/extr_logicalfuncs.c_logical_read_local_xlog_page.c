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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 int read_local_xlog_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 

int
logical_read_local_xlog_page(XLogReaderState *state, XLogRecPtr targetPagePtr,
							 int reqLen, XLogRecPtr targetRecPtr, char *cur_page)
{
	return read_local_xlog_page(state, targetPagePtr, reqLen,
								targetRecPtr, cur_page);
}