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
typedef  int u8 ;
struct se_cmd {unsigned char* t_task_cdb; int /*<<< orphan*/  data_length; int /*<<< orphan*/  se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  NO_SENSE ; 
 int SE_SENSE_BUF ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  UNIT_ATTENTION ; 
 int /*<<< orphan*/  core_scsi3_ua_clear_for_request_sense (struct se_cmd*,int*,int*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int,unsigned char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int target_sense_desc_format (int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static sense_reason_t spc_emulate_request_sense(struct se_cmd *cmd)
{
	unsigned char *cdb = cmd->t_task_cdb;
	unsigned char *rbuf;
	u8 ua_asc = 0, ua_ascq = 0;
	unsigned char buf[SE_SENSE_BUF];
	bool desc_format = target_sense_desc_format(cmd->se_dev);

	memset(buf, 0, SE_SENSE_BUF);

	if (cdb[1] & 0x01) {
		pr_err("REQUEST_SENSE description emulation not"
			" supported\n");
		return TCM_INVALID_CDB_FIELD;
	}

	rbuf = transport_kmap_data_sg(cmd);
	if (!rbuf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	if (!core_scsi3_ua_clear_for_request_sense(cmd, &ua_asc, &ua_ascq))
		scsi_build_sense_buffer(desc_format, buf, UNIT_ATTENTION,
					ua_asc, ua_ascq);
	else
		scsi_build_sense_buffer(desc_format, buf, NO_SENSE, 0x0, 0x0);

	memcpy(rbuf, buf, min_t(u32, sizeof(buf), cmd->data_length));
	transport_kunmap_data_sg(cmd);

	target_complete_cmd(cmd, GOOD);
	return 0;
}