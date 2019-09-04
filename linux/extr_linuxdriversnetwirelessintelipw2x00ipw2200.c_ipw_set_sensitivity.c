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
typedef  int /*<<< orphan*/  u16 ;
struct ipw_sensitivity_calib {int /*<<< orphan*/  beacon_rssi_raw; } ;
struct ipw_priv {int dummy; } ;
typedef  int /*<<< orphan*/  calib ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_SENSITIVITY_CALIB ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_sensitivity_calib*) ; 

__attribute__((used)) static int ipw_set_sensitivity(struct ipw_priv *priv, u16 sens)
{
	struct ipw_sensitivity_calib calib = {
		.beacon_rssi_raw = cpu_to_le16(sens),
	};

	return ipw_send_cmd_pdu(priv, IPW_CMD_SENSITIVITY_CALIB, sizeof(calib),
				&calib);
}