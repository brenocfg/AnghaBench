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
typedef  int /*<<< orphan*/  fnic_trace_data_t ;
struct TYPE_2__ {unsigned long* page_offset; size_t wr_idx; size_t rd_idx; } ;

/* Variables and functions */
 size_t fnic_max_trace_entries ; 
 TYPE_1__ fnic_trace_entries ; 
 int /*<<< orphan*/  fnic_trace_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

fnic_trace_data_t *fnic_trace_get_buf(void)
{
	unsigned long fnic_buf_head;
	unsigned long flags;

	spin_lock_irqsave(&fnic_trace_lock, flags);

	/*
	 * Get next available memory location for writing trace information
	 * at @wr_idx and increment @wr_idx
	 */
	fnic_buf_head =
		fnic_trace_entries.page_offset[fnic_trace_entries.wr_idx];
	fnic_trace_entries.wr_idx++;

	/*
	 * Verify if trace buffer is full then change wd_idx to
	 * start from zero
	 */
	if (fnic_trace_entries.wr_idx >= fnic_max_trace_entries)
		fnic_trace_entries.wr_idx = 0;

	/*
	 * Verify if write index @wr_idx and read index @rd_idx are same then
	 * increment @rd_idx to move to next entry in trace buffer
	 */
	if (fnic_trace_entries.wr_idx == fnic_trace_entries.rd_idx) {
		fnic_trace_entries.rd_idx++;
		if (fnic_trace_entries.rd_idx >= fnic_max_trace_entries)
			fnic_trace_entries.rd_idx = 0;
	}
	spin_unlock_irqrestore(&fnic_trace_lock, flags);
	return (fnic_trace_data_t *)fnic_buf_head;
}