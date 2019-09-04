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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct qla8xxx_minidump_entry_hdr {int dummy; } ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int __qla4_8xxx_minidump_process_rdmem (struct scsi_qla_host*,struct qla8xxx_minidump_entry_hdr*,int /*<<< orphan*/ **) ; 
 int qla4_8xxx_minidump_pex_dma_read (struct scsi_qla_host*,struct qla8xxx_minidump_entry_hdr*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int qla4_8xxx_minidump_process_rdmem(struct scsi_qla_host *ha,
				struct qla8xxx_minidump_entry_hdr *entry_hdr,
				uint32_t **d_ptr)
{
	uint32_t *data_ptr = *d_ptr;
	int rval = QLA_SUCCESS;

	rval = qla4_8xxx_minidump_pex_dma_read(ha, entry_hdr, &data_ptr);
	if (rval != QLA_SUCCESS)
		rval = __qla4_8xxx_minidump_process_rdmem(ha, entry_hdr,
							  &data_ptr);
	*d_ptr = data_ptr;
	return rval;
}