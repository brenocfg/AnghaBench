#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ addr_stride; } ;
struct qla82xx_md_entry_crb {scalar_t__ addr; scalar_t__ op_count; TYPE_1__ crb_strd; } ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla82xx_minidump_process_rdcrb(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t r_addr, r_stride, loop_cnt, i, r_value;
	struct qla82xx_md_entry_crb *crb_hdr;
	uint32_t *data_ptr = *d_ptr;

	crb_hdr = (struct qla82xx_md_entry_crb *)entry_hdr;
	r_addr = crb_hdr->addr;
	r_stride = crb_hdr->crb_strd.addr_stride;
	loop_cnt = crb_hdr->op_count;

	for (i = 0; i < loop_cnt; i++) {
		r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
		*data_ptr++ = cpu_to_le32(r_addr);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	}
	*d_ptr = data_ptr;
}