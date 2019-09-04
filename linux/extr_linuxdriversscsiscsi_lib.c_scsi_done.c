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
struct scsi_cmnd {int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_complete_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_scsi_dispatch_cmd_done (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_done(struct scsi_cmnd *cmd)
{
	trace_scsi_dispatch_cmd_done(cmd);
	blk_complete_request(cmd->request);
}