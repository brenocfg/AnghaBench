#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct ncsi_rsp_pkt {TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  cmd; int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_cmd_ae_pkt {int /*<<< orphan*/  mode; int /*<<< orphan*/  mc_id; } ;
struct ncsi_channel_mode {int enable; int /*<<< orphan*/ * data; } ;
struct ncsi_channel {struct ncsi_channel_mode* modes; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t NCSI_MODE_AEN ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_ae(struct ncsi_request *nr)
{
	struct ncsi_cmd_ae_pkt *cmd;
	struct ncsi_rsp_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_mode *ncm;

	/* Find the package and channel */
	rsp = (struct ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Check if the AEN has been enabled */
	ncm = &nc->modes[NCSI_MODE_AEN];
	if (ncm->enable)
		return 0;

	/* Update to AEN configuration */
	cmd = (struct ncsi_cmd_ae_pkt *)skb_network_header(nr->cmd);
	ncm->enable = 1;
	ncm->data[0] = cmd->mc_id;
	ncm->data[1] = ntohl(cmd->mode);

	return 0;
}