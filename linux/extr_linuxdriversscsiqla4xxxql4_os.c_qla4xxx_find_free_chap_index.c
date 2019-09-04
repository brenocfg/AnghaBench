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
typedef  int uint16_t ;
struct TYPE_2__ {int flt_chap_size; } ;
struct scsi_qla_host {scalar_t__ chap_list; TYPE_1__ hw; } ;
struct ql4_chap_table {scalar_t__ cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAP_VALID_COOKIE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_CHAP_ENTRIES_40XX ; 
 int MAX_RESRV_CHAP_IDX ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ __constant_cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_qla80XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 

__attribute__((used)) static int qla4xxx_find_free_chap_index(struct scsi_qla_host *ha,
					uint16_t *chap_index)
{
	int i, rval;
	int free_index = -1;
	int max_chap_entries = 0;
	struct ql4_chap_table *chap_table;

	if (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
						sizeof(struct ql4_chap_table);
	else
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	if (!ha->chap_list) {
		ql4_printk(KERN_ERR, ha, "CHAP table cache is empty!\n");
		rval = QLA_ERROR;
		goto exit_find_chap;
	}

	for (i = 0; i < max_chap_entries; i++) {
		chap_table = (struct ql4_chap_table *)ha->chap_list + i;

		if ((chap_table->cookie !=
		    __constant_cpu_to_le16(CHAP_VALID_COOKIE)) &&
		   (i > MAX_RESRV_CHAP_IDX)) {
				free_index = i;
				break;
		}
	}

	if (free_index != -1) {
		*chap_index = free_index;
		rval = QLA_SUCCESS;
	} else {
		rval = QLA_ERROR;
	}

exit_find_chap:
	return rval;
}