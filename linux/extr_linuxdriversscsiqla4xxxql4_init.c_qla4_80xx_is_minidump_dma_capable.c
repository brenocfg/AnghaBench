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
struct qla4_8xxx_minidump_template_hdr {int dummy; } ;

/* Variables and functions */
 int BIT_0 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA8022_TEMPLATE_CAP_OFFSET ; 
 int QLA83XX_TEMPLATE_CAP_OFFSET ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla4_80xx_is_minidump_dma_capable(struct scsi_qla_host *ha,
		struct qla4_8xxx_minidump_template_hdr *md_hdr)
{
	int offset = (is_qla8022(ha)) ? QLA8022_TEMPLATE_CAP_OFFSET :
					QLA83XX_TEMPLATE_CAP_OFFSET;
	int rval = 1;
	uint32_t *cap_offset;

	cap_offset = (uint32_t *)((char *)md_hdr + offset);

	if (!(le32_to_cpu(*cap_offset) & BIT_0)) {
		ql4_printk(KERN_INFO, ha, "PEX DMA Not supported %d\n",
			   *cap_offset);
		rval = 0;
	}

	return rval;
}