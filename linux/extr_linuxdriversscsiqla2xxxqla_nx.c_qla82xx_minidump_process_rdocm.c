#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {scalar_t__ nx_pcibase; } ;
struct qla82xx_md_entry_rdocm {scalar_t__ read_addr; scalar_t__ read_addr_stride; scalar_t__ op_count; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 scalar_t__ RD_REG_DWORD (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static void
qla82xx_minidump_process_rdocm(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t r_addr, r_stride, loop_cnt, i, r_value;
	struct qla82xx_md_entry_rdocm *ocm_hdr;
	uint32_t *data_ptr = *d_ptr;

	ocm_hdr = (struct qla82xx_md_entry_rdocm *)entry_hdr;
	r_addr = ocm_hdr->read_addr;
	r_stride = ocm_hdr->read_addr_stride;
	loop_cnt = ocm_hdr->op_count;

	for (i = 0; i < loop_cnt; i++) {
		r_value = RD_REG_DWORD(r_addr + ha->nx_pcibase);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	}
	*d_ptr = data_ptr;
}