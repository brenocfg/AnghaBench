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
struct halmac_tx_page_threshold_info {int dma_queue_sel; int /*<<< orphan*/  threshold; } ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;

/* Variables and functions */
#define  HALMAC_MAP2_EXQ 131 
#define  HALMAC_MAP2_HQ 130 
#define  HALMAC_MAP2_LQ 129 
#define  HALMAC_MAP2_NQ 128 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_TQPNT1 ; 
 int /*<<< orphan*/  REG_TQPNT2 ; 
 int /*<<< orphan*/  REG_TQPNT3 ; 
 int /*<<< orphan*/  REG_TQPNT4 ; 

void halmac_config_sdio_tx_page_threshold_88xx(
	struct halmac_adapter *halmac_adapter,
	struct halmac_tx_page_threshold_info *threshold_info)
{
	struct halmac_api *halmac_api;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	switch (threshold_info->dma_queue_sel) {
	case HALMAC_MAP2_HQ:
		HALMAC_REG_WRITE_32(halmac_adapter, REG_TQPNT1,
				    threshold_info->threshold);
		break;
	case HALMAC_MAP2_NQ:
		HALMAC_REG_WRITE_32(halmac_adapter, REG_TQPNT2,
				    threshold_info->threshold);
		break;
	case HALMAC_MAP2_LQ:
		HALMAC_REG_WRITE_32(halmac_adapter, REG_TQPNT3,
				    threshold_info->threshold);
		break;
	case HALMAC_MAP2_EXQ:
		HALMAC_REG_WRITE_32(halmac_adapter, REG_TQPNT4,
				    threshold_info->threshold);
		break;
	default:
		break;
	}
}