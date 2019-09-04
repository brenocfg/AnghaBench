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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct lpfc_vport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  date; int /*<<< orphan*/  revision; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number; int /*<<< orphan*/  vendor_name; } ;
struct fc_rdp_opd_sfp_desc {void* length; TYPE_1__ opd_info; void* tag; } ;

/* Variables and functions */
 int RDP_OPD_DESC_TAG ; 
 size_t SSF_DATE_CODE ; 
 size_t SSF_VENDOR_NAME ; 
 size_t SSF_VENDOR_PN ; 
 size_t SSF_VENDOR_REV ; 
 size_t SSF_VENDOR_SN ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_opd_desc(struct fc_rdp_opd_sfp_desc *desc,
		      uint8_t *page_a0, struct lpfc_vport *vport)
{
	desc->tag = cpu_to_be32(RDP_OPD_DESC_TAG);
	memcpy(desc->opd_info.vendor_name, &page_a0[SSF_VENDOR_NAME], 16);
	memcpy(desc->opd_info.model_number, &page_a0[SSF_VENDOR_PN], 16);
	memcpy(desc->opd_info.serial_number, &page_a0[SSF_VENDOR_SN], 16);
	memcpy(desc->opd_info.revision, &page_a0[SSF_VENDOR_REV], 4);
	memcpy(desc->opd_info.date, &page_a0[SSF_DATE_CODE], 8);
	desc->length = cpu_to_be32(sizeof(desc->opd_info));
	return sizeof(struct fc_rdp_opd_sfp_desc);
}