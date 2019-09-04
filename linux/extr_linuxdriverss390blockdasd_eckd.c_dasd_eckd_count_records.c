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
struct eckd_count {int head; int record; } ;

/* Variables and functions */

__attribute__((used)) static int dasd_eckd_count_records(struct eckd_count *fmt_buffer, int start,
				   int max)
{
	int head;
	int i;

	head = fmt_buffer[start].head;

	/*
	 * There are 3 conditions where we stop counting:
	 * - if data reoccurs (same head and record may reoccur), which may
	 *   happen due to the way DASD_ECKD_CCW_READ_COUNT works
	 * - when the head changes, because we're iterating over several tracks
	 *   then (DASD_ECKD_CCW_READ_COUNT_MT)
	 * - when we've reached the end of sensible data in the buffer (the
	 *   record will be 0 then)
	 */
	for (i = start; i < max; i++) {
		if (i > start) {
			if ((fmt_buffer[i].head == head &&
			    fmt_buffer[i].record == 1) ||
			    fmt_buffer[i].head != head ||
			    fmt_buffer[i].record == 0)
				break;
		}
	}

	return i - start;
}