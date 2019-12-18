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
struct ncsi_request {int enabled; int /*<<< orphan*/  cmd; int /*<<< orphan*/  timer; int /*<<< orphan*/  id; int /*<<< orphan*/  nlhdr; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; } ;
struct ncsi_cmd_handler {unsigned char type; int (* handler ) (int /*<<< orphan*/ ,struct ncsi_cmd_arg*) ;scalar_t__ payload; } ;
struct ncsi_cmd_arg {scalar_t__ req_flags; unsigned char type; scalar_t__ payload; int /*<<< orphan*/  id; TYPE_3__* info; TYPE_2__* ndp; } ;
struct ethhdr {int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_proto; } ;
struct TYPE_6__ {int /*<<< orphan*/ * nlhdr; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ ndev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ncsi_cmd_handler*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_NCSI ; 
 int HZ ; 
 unsigned char NCSI_PKT_CMD_OEM ; 
 scalar_t__ NCSI_REQ_FLAG_NETLINK_DRIVEN ; 
 int dev_queue_xmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ncsi_request* ncsi_alloc_command (struct ncsi_cmd_arg*) ; 
 struct ncsi_cmd_handler* ncsi_cmd_handlers ; 
 int /*<<< orphan*/  ncsi_free_request (struct ncsi_request*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  skb_get (int /*<<< orphan*/ ) ; 
 struct ethhdr* skb_push (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct ncsi_cmd_arg*) ; 

int ncsi_xmit_cmd(struct ncsi_cmd_arg *nca)
{
	struct ncsi_cmd_handler *nch = NULL;
	struct ncsi_request *nr;
	unsigned char type;
	struct ethhdr *eh;
	int i, ret;

	/* Use OEM generic handler for Netlink request */
	if (nca->req_flags == NCSI_REQ_FLAG_NETLINK_DRIVEN)
		type = NCSI_PKT_CMD_OEM;
	else
		type = nca->type;

	/* Search for the handler */
	for (i = 0; i < ARRAY_SIZE(ncsi_cmd_handlers); i++) {
		if (ncsi_cmd_handlers[i].type == type) {
			if (ncsi_cmd_handlers[i].handler)
				nch = &ncsi_cmd_handlers[i];
			else
				nch = NULL;

			break;
		}
	}

	if (!nch) {
		netdev_err(nca->ndp->ndev.dev,
			   "Cannot send packet with type 0x%02x\n", nca->type);
		return -ENOENT;
	}

	/* Get packet payload length and allocate the request
	 * It is expected that if length set as negative in
	 * handler structure means caller is initializing it
	 * and setting length in nca before calling xmit function
	 */
	if (nch->payload >= 0)
		nca->payload = nch->payload;
	nr = ncsi_alloc_command(nca);
	if (!nr)
		return -ENOMEM;

	/* track netlink information */
	if (nca->req_flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) {
		nr->snd_seq = nca->info->snd_seq;
		nr->snd_portid = nca->info->snd_portid;
		nr->nlhdr = *nca->info->nlhdr;
	}

	/* Prepare the packet */
	nca->id = nr->id;
	ret = nch->handler(nr->cmd, nca);
	if (ret) {
		ncsi_free_request(nr);
		return ret;
	}

	/* Fill the ethernet header */
	eh = skb_push(nr->cmd, sizeof(*eh));
	eh->h_proto = htons(ETH_P_NCSI);
	eth_broadcast_addr(eh->h_dest);
	eth_broadcast_addr(eh->h_source);

	/* Start the timer for the request that might not have
	 * corresponding response. Given NCSI is an internal
	 * connection a 1 second delay should be sufficient.
	 */
	nr->enabled = true;
	mod_timer(&nr->timer, jiffies + 1 * HZ);

	/* Send NCSI packet */
	skb_get(nr->cmd);
	ret = dev_queue_xmit(nr->cmd);
	if (ret < 0) {
		ncsi_free_request(nr);
		return ret;
	}

	return 0;
}