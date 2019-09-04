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
struct iscsi_session {struct ddb_entry* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct ddb_entry {scalar_t__ ddb_type; int /*<<< orphan*/  sess; int /*<<< orphan*/  fw_ddb_device_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDB_DS_SESSION_FAILED ; 
 scalar_t__ FLASH_DDB ; 
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  iscsi_block_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_failure (struct iscsi_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4xxx_fail_session(struct iscsi_cls_session *cls_session)
{
	struct iscsi_session *sess;
	struct ddb_entry *ddb_entry;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ddb_entry->fw_ddb_device_state = DDB_DS_SESSION_FAILED;

	if (ddb_entry->ddb_type == FLASH_DDB)
		iscsi_block_session(ddb_entry->sess);
	else
		iscsi_session_failure(cls_session->dd_data,
				      ISCSI_ERR_CONN_FAILED);
}