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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_POWER_MODE ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
#define  IPW_POWER_AC 129 
#define  IPW_POWER_BATTERY 128 
 int IPW_POWER_INDEX_3 ; 
 int IPW_POWER_MODE_CAM ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_send_power_mode(struct ipw_priv *priv, u32 mode)
{
	__le32 param;

	if (!priv) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	/* If on battery, set to 3, if AC set to CAM, else user
	 * level */
	switch (mode) {
	case IPW_POWER_BATTERY:
		param = cpu_to_le32(IPW_POWER_INDEX_3);
		break;
	case IPW_POWER_AC:
		param = cpu_to_le32(IPW_POWER_MODE_CAM);
		break;
	default:
		param = cpu_to_le32(mode);
		break;
	}

	return ipw_send_cmd_pdu(priv, IPW_CMD_POWER_MODE, sizeof(param),
				&param);
}