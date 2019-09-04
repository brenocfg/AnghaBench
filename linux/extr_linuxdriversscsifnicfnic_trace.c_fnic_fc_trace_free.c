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
struct TYPE_2__ {int /*<<< orphan*/ * page_offset; } ;

/* Variables and functions */
 TYPE_1__ fc_trace_entries ; 
 scalar_t__ fnic_fc_ctlr_trace_buf_p ; 
 int /*<<< orphan*/  fnic_fc_trace_debugfs_terminate () ; 
 scalar_t__ fnic_fc_tracing_enabled ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void fnic_fc_trace_free(void)
{
	fnic_fc_tracing_enabled = 0;
	fnic_fc_trace_debugfs_terminate();
	if (fc_trace_entries.page_offset) {
		vfree((void *)fc_trace_entries.page_offset);
		fc_trace_entries.page_offset = NULL;
	}
	if (fnic_fc_ctlr_trace_buf_p) {
		vfree((void *)fnic_fc_ctlr_trace_buf_p);
		fnic_fc_ctlr_trace_buf_p = 0;
	}
	pr_info("fnic:Successfully FC_CTLR Freed Trace Buffer\n");
}