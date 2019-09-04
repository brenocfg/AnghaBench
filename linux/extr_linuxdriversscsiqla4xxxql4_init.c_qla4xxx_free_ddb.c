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
struct scsi_qla_host {int /*<<< orphan*/  tot_ddbs; struct ddb_entry** fw_ddb_index_map; } ;
struct ddb_entry {size_t fw_ddb_index; } ;

/* Variables and functions */
 scalar_t__ INVALID_ENTRY ; 

void qla4xxx_free_ddb(struct scsi_qla_host *ha,
    struct ddb_entry *ddb_entry)
{
	/* Remove device pointer from index mapping arrays */
	ha->fw_ddb_index_map[ddb_entry->fw_ddb_index] =
		(struct ddb_entry *) INVALID_ENTRY;
	ha->tot_ddbs--;
}