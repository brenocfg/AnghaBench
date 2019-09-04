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
struct se_cmd {unsigned char* t_task_cdb; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
sbc_emulate_startstop(struct se_cmd *cmd)
{
	unsigned char *cdb = cmd->t_task_cdb;

	/*
	 * See sbc3r36 section 5.25
	 * Immediate bit should be set since there is nothing to complete
	 * POWER CONDITION MODIFIER 0h
	 */
	if (!(cdb[1] & 1) || cdb[2] || cdb[3])
		return TCM_INVALID_CDB_FIELD;

	/*
	 * See sbc3r36 section 5.25
	 * POWER CONDITION 0h START_VALID - process START and LOEJ
	 */
	if (cdb[4] >> 4 & 0xf)
		return TCM_INVALID_CDB_FIELD;

	/*
	 * See sbc3r36 section 5.25
	 * LOEJ 0h - nothing to load or unload
	 * START 1h - we are ready
	 */
	if (!(cdb[4] & 1) || (cdb[4] & 2) || (cdb[4] & 4))
		return TCM_INVALID_CDB_FIELD;

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	return 0;
}