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
struct auxtrace_record {int (* snapshot_finish ) (struct auxtrace_record*) ;} ;

/* Variables and functions */
 int stub1 (struct auxtrace_record*) ; 

int auxtrace_record__snapshot_finish(struct auxtrace_record *itr, bool on_exit)
{
	if (!on_exit && itr && itr->snapshot_finish)
		return itr->snapshot_finish(itr);
	return 0;
}