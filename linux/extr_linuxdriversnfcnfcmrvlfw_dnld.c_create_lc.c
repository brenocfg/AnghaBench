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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct nfcmrvl_private {int /*<<< orphan*/  ndev; TYPE_1__ fw_dnld; } ;

/* Variables and functions */
 int NCI_CORE_LC_PROP_FW_DL ; 
 int /*<<< orphan*/  NCI_OP_CORE_CONN_CREATE_CMD ; 
 int /*<<< orphan*/  STATE_OPEN_LC ; 
 int /*<<< orphan*/  nci_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void create_lc(struct nfcmrvl_private *priv)
{
	uint8_t param[2] = { NCI_CORE_LC_PROP_FW_DL, 0x0 };

	priv->fw_dnld.state = STATE_OPEN_LC;
	nci_send_cmd(priv->ndev, NCI_OP_CORE_CONN_CREATE_CMD, 2, param);
}