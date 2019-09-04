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
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; TYPE_1__* request; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  scmd_name (struct scsi_cmnd const*) ; 
 int /*<<< orphan*/  scsi_log_print_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scsi_print_sense(const struct scsi_cmnd *cmd)
{
	scsi_log_print_sense(cmd->device, scmd_name(cmd), cmd->request->tag,
			     cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE);
}