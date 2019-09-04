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
struct scsi_cmnd {unsigned char* cmnd; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int CMD_MODE_UNKNOWN ; 
 int CMD_SURELY_BLOCK_MODE ; 
 int CMD_SURELY_BYTE_MODE ; 
 unsigned char READ_10 ; 
 unsigned char READ_6 ; 
 unsigned char READ_BUFFER ; 
 unsigned char READ_DEFECT_DATA ; 
 unsigned char READ_LONG ; 
 unsigned char READ_REVERSE ; 
 unsigned char RECOVER_BUFFERED_DATA ; 
 scalar_t__ TYPE_TAPE ; 

__attribute__((used)) static int falcon_classify_cmd(struct scsi_cmnd *cmd)
{
	unsigned char opcode = cmd->cmnd[0];

	if (opcode == READ_DEFECT_DATA || opcode == READ_LONG ||
	    opcode == READ_BUFFER)
		return CMD_SURELY_BYTE_MODE;
	else if (opcode == READ_6 || opcode == READ_10 ||
		 opcode == 0xa8 /* READ_12 */ || opcode == READ_REVERSE ||
		 opcode == RECOVER_BUFFERED_DATA) {
		/* In case of a sequential-access target (tape), special care is
		 * needed here: The transfer is block-mode only if the 'fixed' bit is
		 * set! */
		if (cmd->device->type == TYPE_TAPE && !(cmd->cmnd[1] & 1))
			return CMD_SURELY_BYTE_MODE;
		else
			return CMD_SURELY_BLOCK_MODE;
	} else
		return CMD_MODE_UNKNOWN;
}