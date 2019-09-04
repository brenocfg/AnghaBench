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
struct ipw_tx_power {int dummy; } ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_TX_POWER ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_tx_power*) ; 

__attribute__((used)) static int ipw_send_tx_power(struct ipw_priv *priv, struct ipw_tx_power *power)
{
	if (!priv || !power) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	return ipw_send_cmd_pdu(priv, IPW_CMD_TX_POWER, sizeof(*power), power);
}