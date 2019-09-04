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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct iscsi_session {scalar_t__ discovery_parent_idx; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct dev_db_entry {int /*<<< orphan*/  ddb_link; } ;
struct ddb_entry {struct iscsi_cls_session* sess; } ;

/* Variables and functions */
 scalar_t__ DDB_NO_LINK ; 
 scalar_t__ MAX_DEV_DB_ENTRIES ; 
 scalar_t__ MAX_DEV_DB_ENTRIES_40XX ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4xxx_update_sess_disc_idx(struct scsi_qla_host *ha,
					 struct ddb_entry *ddb_entry,
					 struct dev_db_entry *fw_ddb_entry)
{
	struct iscsi_cls_session *cls_sess;
	struct iscsi_session *sess;
	uint32_t max_ddbs = 0;
	uint16_t ddb_link = -1;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	cls_sess = ddb_entry->sess;
	sess = cls_sess->dd_data;

	ddb_link = le16_to_cpu(fw_ddb_entry->ddb_link);
	if (ddb_link < max_ddbs)
		sess->discovery_parent_idx = ddb_link;
	else
		sess->discovery_parent_idx = DDB_NO_LINK;
}