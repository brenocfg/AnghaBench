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
struct ncsi_rsp_gvi_pkt {int /*<<< orphan*/  mf_id; int /*<<< orphan*/ * pci_ids; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  alpha2; int /*<<< orphan*/  ncsi_version; TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_version {void* mf_id; int /*<<< orphan*/ * pci_ids; void* fw_version; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  alpha2; void* version; } ;
struct ncsi_channel {struct ncsi_channel_version version; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_gvi(struct ncsi_request *nr)
{
	struct ncsi_rsp_gvi_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_version *ncv;
	int i;

	/* Find the channel */
	rsp = (struct ncsi_rsp_gvi_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Update to channel's version info */
	ncv = &nc->version;
	ncv->version = ntohl(rsp->ncsi_version);
	ncv->alpha2 = rsp->alpha2;
	memcpy(ncv->fw_name, rsp->fw_name, 12);
	ncv->fw_version = ntohl(rsp->fw_version);
	for (i = 0; i < ARRAY_SIZE(ncv->pci_ids); i++)
		ncv->pci_ids[i] = ntohs(rsp->pci_ids[i]);
	ncv->mf_id = ntohl(rsp->mf_id);

	return 0;
}