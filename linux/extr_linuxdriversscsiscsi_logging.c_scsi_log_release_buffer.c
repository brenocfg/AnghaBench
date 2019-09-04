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
 int SCSI_LOG_SPOOLSIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  scsi_format_log ; 
 int test_and_clear_bit (unsigned long,int /*<<< orphan*/ *) ; 
 struct scsi_log_buf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scsi_log_release_buffer(char *bufptr)
{
	struct scsi_log_buf *buf;
	unsigned long idx;
	int ret;

	buf = this_cpu_ptr(&scsi_format_log);
	if (bufptr >= buf->buffer &&
	    bufptr < buf->buffer + SCSI_LOG_SPOOLSIZE) {
		idx = (bufptr - buf->buffer) / SCSI_LOG_BUFSIZE;
		ret = test_and_clear_bit(idx, &buf->map);
		WARN_ON(!ret);
	}
	preempt_enable();
}