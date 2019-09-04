#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  delay_time; } ;
struct TYPE_6__ {int rf_path; int /*<<< orphan*/  offset; int /*<<< orphan*/  value; int /*<<< orphan*/  msk_en; int /*<<< orphan*/  msk; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  value; int /*<<< orphan*/  msk_en; int /*<<< orphan*/  msk; } ;
struct TYPE_8__ {TYPE_3__ DELAY_TIME; TYPE_2__ RF_REG_W; TYPE_1__ MAC_REG_W; } ;
struct halmac_phy_parameter_info {int cmd_id; TYPE_4__ content; } ;
struct halmac_config_para_info {int /*<<< orphan*/  offset_accumulation; int /*<<< orphan*/  value_accumulation; } ;
struct halmac_adapter {struct halmac_config_para_info config_para_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_FW_OFFLOAD_CMD_SIZE_88XX ; 
#define  HALMAC_PARAMETER_CMD_BB_W16 137 
#define  HALMAC_PARAMETER_CMD_BB_W32 136 
#define  HALMAC_PARAMETER_CMD_BB_W8 135 
#define  HALMAC_PARAMETER_CMD_DELAY_MS 134 
#define  HALMAC_PARAMETER_CMD_DELAY_US 133 
#define  HALMAC_PARAMETER_CMD_END 132 
#define  HALMAC_PARAMETER_CMD_MAC_W16 131 
#define  HALMAC_PARAMETER_CMD_MAC_W32 130 
#define  HALMAC_PARAMETER_CMD_MAC_W8 129 
#define  HALMAC_PARAMETER_CMD_RF_W 128 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_DATA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_DELAY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_IO_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_IO_CMD (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_LENGTH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_MASK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_MSK_EN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_RF_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_PARAMETER_INFO_SET_RF_PATH (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_enqueue_para_buff_88xx(struct halmac_adapter *halmac_adapter,
			      struct halmac_phy_parameter_info *para_info,
			      u8 *curr_buff_wptr, bool *end_cmd)
{
	struct halmac_config_para_info *config_para_info =
		&halmac_adapter->config_para_info;

	*end_cmd = false;

	PHY_PARAMETER_INFO_SET_LENGTH(curr_buff_wptr,
				      HALMAC_FW_OFFLOAD_CMD_SIZE_88XX);
	PHY_PARAMETER_INFO_SET_IO_CMD(curr_buff_wptr, para_info->cmd_id);

	switch (para_info->cmd_id) {
	case HALMAC_PARAMETER_CMD_BB_W8:
	case HALMAC_PARAMETER_CMD_BB_W16:
	case HALMAC_PARAMETER_CMD_BB_W32:
	case HALMAC_PARAMETER_CMD_MAC_W8:
	case HALMAC_PARAMETER_CMD_MAC_W16:
	case HALMAC_PARAMETER_CMD_MAC_W32:
		PHY_PARAMETER_INFO_SET_IO_ADDR(
			curr_buff_wptr, para_info->content.MAC_REG_W.offset);
		PHY_PARAMETER_INFO_SET_DATA(curr_buff_wptr,
					    para_info->content.MAC_REG_W.value);
		PHY_PARAMETER_INFO_SET_MASK(curr_buff_wptr,
					    para_info->content.MAC_REG_W.msk);
		PHY_PARAMETER_INFO_SET_MSK_EN(
			curr_buff_wptr, para_info->content.MAC_REG_W.msk_en);
		config_para_info->value_accumulation +=
			para_info->content.MAC_REG_W.value;
		config_para_info->offset_accumulation +=
			para_info->content.MAC_REG_W.offset;
		break;
	case HALMAC_PARAMETER_CMD_RF_W:
		/*In rf register, the address is only 1 byte*/
		PHY_PARAMETER_INFO_SET_RF_ADDR(
			curr_buff_wptr, para_info->content.RF_REG_W.offset);
		PHY_PARAMETER_INFO_SET_RF_PATH(
			curr_buff_wptr, para_info->content.RF_REG_W.rf_path);
		PHY_PARAMETER_INFO_SET_DATA(curr_buff_wptr,
					    para_info->content.RF_REG_W.value);
		PHY_PARAMETER_INFO_SET_MASK(curr_buff_wptr,
					    para_info->content.RF_REG_W.msk);
		PHY_PARAMETER_INFO_SET_MSK_EN(
			curr_buff_wptr, para_info->content.RF_REG_W.msk_en);
		config_para_info->value_accumulation +=
			para_info->content.RF_REG_W.value;
		config_para_info->offset_accumulation +=
			(para_info->content.RF_REG_W.offset +
			 (para_info->content.RF_REG_W.rf_path << 8));
		break;
	case HALMAC_PARAMETER_CMD_DELAY_US:
	case HALMAC_PARAMETER_CMD_DELAY_MS:
		PHY_PARAMETER_INFO_SET_DELAY_VALUE(
			curr_buff_wptr,
			para_info->content.DELAY_TIME.delay_time);
		break;
	case HALMAC_PARAMETER_CMD_END:
		*end_cmd = true;
		break;
	default:
		pr_err(" halmac_send_h2c_phy_parameter_88xx illegal cmd_id!!\n");
		break;
	}

	return HALMAC_RET_SUCCESS;
}