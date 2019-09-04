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
struct ipr_cmnd {TYPE_1__* scsi_cmd; } ;
struct TYPE_2__ {void* device; } ;

/* Variables and functions */

__attribute__((used)) static int ipr_match_lun(struct ipr_cmnd *ipr_cmd, void *device)
{
	if (ipr_cmd->scsi_cmd && ipr_cmd->scsi_cmd->device == device)
		return 1;
	return 0;
}