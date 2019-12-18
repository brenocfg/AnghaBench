#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecData ;
struct TYPE_2__ {int in_use; } ;

/* Variables and functions */
 int begininsert_called ; 
 scalar_t__ curinsert_flags ; 
 int /*<<< orphan*/  mainrdata_head ; 
 int /*<<< orphan*/ * mainrdata_last ; 
 scalar_t__ mainrdata_len ; 
 int max_registered_block_id ; 
 scalar_t__ num_rdatas ; 
 TYPE_1__* registered_buffers ; 

void
XLogResetInsertion(void)
{
	int			i;

	for (i = 0; i < max_registered_block_id; i++)
		registered_buffers[i].in_use = false;

	num_rdatas = 0;
	max_registered_block_id = 0;
	mainrdata_len = 0;
	mainrdata_last = (XLogRecData *) &mainrdata_head;
	curinsert_flags = 0;
	begininsert_called = false;
}