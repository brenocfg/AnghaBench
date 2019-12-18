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
struct TYPE_2__ {int (* read_char ) () ;} ;

/* Variables and functions */
 int NO_POLL_CHAR ; 
 TYPE_1__* dbg_io_ops ; 
 int stub1 () ; 
 int stub2 () ; 

__attribute__((used)) static int gdbstub_read_wait(void)
{
	int ret = dbg_io_ops->read_char();
	while (ret == NO_POLL_CHAR)
		ret = dbg_io_ops->read_char();
	return ret;
}