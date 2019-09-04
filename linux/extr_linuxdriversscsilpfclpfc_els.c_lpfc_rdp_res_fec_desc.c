#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {void* UncorrectableBlocks; void* CorrectedBlocks; } ;
struct fc_fec_rdp_desc {void* length; TYPE_1__ info; void* tag; } ;
struct TYPE_6__ {int fecCorrBlkCount; int fecUncorrBlkCount; } ;
typedef  TYPE_2__ READ_LNK_VAR ;

/* Variables and functions */
 int RDP_FEC_DESC_TAG ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  lpfc_read_link_stat_gec2 ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_fec_desc(struct fc_fec_rdp_desc *desc, READ_LNK_VAR *stat)
{
	if (bf_get(lpfc_read_link_stat_gec2, stat) == 0)
		return 0;
	desc->tag = cpu_to_be32(RDP_FEC_DESC_TAG);

	desc->info.CorrectedBlocks =
		cpu_to_be32(stat->fecCorrBlkCount);
	desc->info.UncorrectableBlocks =
		cpu_to_be32(stat->fecUncorrBlkCount);

	desc->length = cpu_to_be32(sizeof(desc->info));

	return sizeof(struct fc_fec_rdp_desc);
}