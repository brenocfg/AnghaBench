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
struct se_cmd {int se_cmd_flags; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int SCF_BIDI ; 
 int /*<<< orphan*/  TCM_UNSUPPORTED_SCSI_OPCODE ; 
 int /*<<< orphan*/  passthrough_parse_cdb (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pscsi_execute_cmd ; 

__attribute__((used)) static sense_reason_t
pscsi_parse_cdb(struct se_cmd *cmd)
{
	if (cmd->se_cmd_flags & SCF_BIDI)
		return TCM_UNSUPPORTED_SCSI_OPCODE;

	return passthrough_parse_cdb(cmd, pscsi_execute_cmd);
}