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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int ac_empty; int ac_oqt_number; } ;
struct halmac_adapter {TYPE_1__ sdio_free_space; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_queue_select { ____Placeholder_halmac_queue_select } halmac_queue_select ;

/* Variables and functions */
 int /*<<< orphan*/  GET_TX_DESC_QSEL (int*) ; 
#define  HALMAC_QUEUE_SELECT_BE 135 
#define  HALMAC_QUEUE_SELECT_BE_V2 134 
#define  HALMAC_QUEUE_SELECT_BK 133 
#define  HALMAC_QUEUE_SELECT_BK_V2 132 
#define  HALMAC_QUEUE_SELECT_VI 131 
#define  HALMAC_QUEUE_SELECT_VI_V2 130 
#define  HALMAC_QUEUE_SELECT_VO 129 
#define  HALMAC_QUEUE_SELECT_VO_V2 128 
 int HALMAC_RET_OQT_NOT_ENOUGH ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  halmac_update_oqt_free_space_88xx (struct halmac_adapter*) ; 

enum halmac_ret_status
halmac_check_oqt_88xx(struct halmac_adapter *halmac_adapter, u32 tx_agg_num,
		      u8 *halmac_buf)
{
	u32 counter = 10;

	/*S0, S1 are not allowed to use, 0x4E4[0] should be 0. Soar 20160323*/
	/*no need to check non_ac_oqt_number. HI and MGQ blocked will cause
	 *protocal issue before H_OQT being full
	 */
	switch ((enum halmac_queue_select)GET_TX_DESC_QSEL(halmac_buf)) {
	case HALMAC_QUEUE_SELECT_VO:
	case HALMAC_QUEUE_SELECT_VO_V2:
	case HALMAC_QUEUE_SELECT_VI:
	case HALMAC_QUEUE_SELECT_VI_V2:
	case HALMAC_QUEUE_SELECT_BE:
	case HALMAC_QUEUE_SELECT_BE_V2:
	case HALMAC_QUEUE_SELECT_BK:
	case HALMAC_QUEUE_SELECT_BK_V2:
		counter = 10;
		do {
			if (halmac_adapter->sdio_free_space.ac_empty > 0) {
				halmac_adapter->sdio_free_space.ac_empty -= 1;
				break;
			}

			if (halmac_adapter->sdio_free_space.ac_oqt_number >=
			    tx_agg_num) {
				halmac_adapter->sdio_free_space.ac_oqt_number -=
					(u8)tx_agg_num;
				break;
			}

			halmac_update_oqt_free_space_88xx(halmac_adapter);

			counter--;
			if (counter == 0)
				return HALMAC_RET_OQT_NOT_ENOUGH;
		} while (1);
		break;
	default:
		break;
	}

	return HALMAC_RET_SUCCESS;
}