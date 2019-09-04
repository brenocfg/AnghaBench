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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int ahd_linux_queue_abort_cmd (struct scsi_cmnd*) ; 

__attribute__((used)) static int
ahd_linux_abort(struct scsi_cmnd *cmd)
{
	int error;
	
	error = ahd_linux_queue_abort_cmd(cmd);

	return error;
}