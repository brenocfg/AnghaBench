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
typedef  int uint32_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int DDB_DS_NO_CONNECTION_ACTIVE ; 
 int DDB_DS_SESSION_FAILED ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MAX_DEV_DB_ENTRIES ; 
 int MAX_DEV_DB_ENTRIES_40XX ; 
 int QLA_ERROR ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,int) ; 
 int qla4xxx_clear_ddb_entry (struct scsi_qla_host*,int) ; 
 int qla4xxx_get_fwddb_entry (struct scsi_qla_host*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qla4xxx_free_ddb_index(struct scsi_qla_host *ha)
{
	int max_ddbs;
	int ret;
	uint32_t idx = 0, next_idx = 0;
	uint32_t state = 0, conn_err = 0;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	for (idx = 0; idx < max_ddbs; idx = next_idx) {
		ret = qla4xxx_get_fwddb_entry(ha, idx, NULL, 0, NULL,
					      &next_idx, &state, &conn_err,
						NULL, NULL);
		if (ret == QLA_ERROR) {
			next_idx++;
			continue;
		}
		if (state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAILED) {
			DEBUG2(ql4_printk(KERN_INFO, ha,
					  "Freeing DDB index = 0x%x\n", idx));
			ret = qla4xxx_clear_ddb_entry(ha, idx);
			if (ret == QLA_ERROR)
				ql4_printk(KERN_ERR, ha,
					   "Unable to clear DDB index = "
					   "0x%x\n", idx);
		}
		if (next_idx == 0)
			break;
	}
}