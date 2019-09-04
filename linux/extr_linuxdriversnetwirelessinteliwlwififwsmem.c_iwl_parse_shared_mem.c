#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_shared_mem_cfg_v2 {void** internal_txfifo_size; void* internal_txfifo_addr; void** rxfifo_size; void** txfifo_size; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct TYPE_6__ {int num_lmacs; int num_txfifo_entries; void** internal_txfifo_size; void* internal_txfifo_addr; void* rxfifo2_size; TYPE_1__* lmac; } ;
struct iwl_fw_runtime {TYPE_3__ smem_cfg; TYPE_2__* fw; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_4__ {void* rxfifo1_size; void** txfifo_size; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 

__attribute__((used)) static void iwl_parse_shared_mem(struct iwl_fw_runtime *fwrt,
				 struct iwl_rx_packet *pkt)
{
	struct iwl_shared_mem_cfg_v2 *mem_cfg = (void *)pkt->data;
	int i;

	fwrt->smem_cfg.num_lmacs = 1;

	fwrt->smem_cfg.num_txfifo_entries = ARRAY_SIZE(mem_cfg->txfifo_size);
	for (i = 0; i < ARRAY_SIZE(mem_cfg->txfifo_size); i++)
		fwrt->smem_cfg.lmac[0].txfifo_size[i] =
			le32_to_cpu(mem_cfg->txfifo_size[i]);

	fwrt->smem_cfg.lmac[0].rxfifo1_size =
		le32_to_cpu(mem_cfg->rxfifo_size[0]);
	fwrt->smem_cfg.rxfifo2_size = le32_to_cpu(mem_cfg->rxfifo_size[1]);

	/* new API has more data, from rxfifo_addr field and on */
	if (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG)) {
		BUILD_BUG_ON(sizeof(fwrt->smem_cfg.internal_txfifo_size) !=
			     sizeof(mem_cfg->internal_txfifo_size));

		fwrt->smem_cfg.internal_txfifo_addr =
			le32_to_cpu(mem_cfg->internal_txfifo_addr);

		for (i = 0;
		     i < ARRAY_SIZE(fwrt->smem_cfg.internal_txfifo_size);
		     i++)
			fwrt->smem_cfg.internal_txfifo_size[i] =
				le32_to_cpu(mem_cfg->internal_txfifo_size[i]);
	}
}