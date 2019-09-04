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
struct scsi_log_buf {char* buffer; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int SCSI_LOG_BUFSIZE ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  scsi_format_log ; 
 scalar_t__ test_and_set_bit (unsigned long,int /*<<< orphan*/ *) ; 
 struct scsi_log_buf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *scsi_log_reserve_buffer(size_t *len)
{
	struct scsi_log_buf *buf;
	unsigned long map_bits = sizeof(buf->buffer) / SCSI_LOG_BUFSIZE;
	unsigned long idx = 0;

	preempt_disable();
	buf = this_cpu_ptr(&scsi_format_log);
	idx = find_first_zero_bit(&buf->map, map_bits);
	if (likely(idx < map_bits)) {
		while (test_and_set_bit(idx, &buf->map)) {
			idx = find_next_zero_bit(&buf->map, map_bits, idx);
			if (idx >= map_bits)
				break;
		}
	}
	if (WARN_ON(idx >= map_bits)) {
		preempt_enable();
		return NULL;
	}
	*len = SCSI_LOG_BUFSIZE;
	return buf->buffer + idx * SCSI_LOG_BUFSIZE;
}