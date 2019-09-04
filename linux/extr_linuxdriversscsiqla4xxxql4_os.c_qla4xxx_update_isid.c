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
typedef  int uint8_t ;
struct scsi_qla_host {int dummy; } ;
struct list_head {int dummy; } ;
struct dev_db_entry {int* isid; } ;

/* Variables and functions */
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ qla4xxx_check_existing_isid (struct list_head*,int*) ; 

__attribute__((used)) static int qla4xxx_update_isid(struct scsi_qla_host *ha,
			       struct list_head *list_nt,
			       struct dev_db_entry *fw_ddb_entry)
{
	uint8_t base_value, i;

	base_value = fw_ddb_entry->isid[1] & 0x1f;
	for (i = 0; i < 8; i++) {
		fw_ddb_entry->isid[1] = (base_value | (i << 5));
		if (qla4xxx_check_existing_isid(list_nt, fw_ddb_entry->isid))
			break;
	}

	if (!qla4xxx_check_existing_isid(list_nt, fw_ddb_entry->isid))
		return QLA_ERROR;

	return QLA_SUCCESS;
}