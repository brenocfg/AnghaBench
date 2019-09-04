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
struct hv_do_fcopy {scalar_t__ size; int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
#define  ENOSPC 128 
 int HV_ERROR_DISK_FULL ; 
 int HV_E_FAIL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int errno ; 
 int /*<<< orphan*/  filesize ; 
 scalar_t__ pwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_fd ; 

__attribute__((used)) static int hv_copy_data(struct hv_do_fcopy *cpmsg)
{
	ssize_t bytes_written;
	int ret = 0;

	bytes_written = pwrite(target_fd, cpmsg->data, cpmsg->size,
				cpmsg->offset);

	filesize += cpmsg->size;
	if (bytes_written != cpmsg->size) {
		switch (errno) {
		case ENOSPC:
			ret = HV_ERROR_DISK_FULL;
			break;
		default:
			ret = HV_E_FAIL;
			break;
		}
		syslog(LOG_ERR, "pwrite failed to write %llu bytes: %ld (%s)",
		       filesize, (long)bytes_written, strerror(errno));
	}

	return ret;
}