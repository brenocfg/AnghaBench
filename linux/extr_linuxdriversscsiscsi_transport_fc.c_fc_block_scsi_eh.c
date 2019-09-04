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
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct fc_rport {int dummy; } ;

/* Variables and functions */
 int FAST_IO_FAIL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int fc_block_rport (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_target (int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 

int fc_block_scsi_eh(struct scsi_cmnd *cmnd)
{
	struct fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));

	if (WARN_ON_ONCE(!rport))
		return FAST_IO_FAIL;

	return fc_block_rport(rport);
}