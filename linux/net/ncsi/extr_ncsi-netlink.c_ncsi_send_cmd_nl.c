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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ncsi_pkt_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ncsi_dev_priv {TYPE_1__ ndev; } ;
struct ncsi_cmd_arg {unsigned char package; unsigned char channel; unsigned char* data; int /*<<< orphan*/  payload; struct genl_info* info; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  type; struct ncsi_dev_priv* ndp; } ;
struct genl_info {int /*<<< orphan*/  nlhdr; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 size_t NCSI_ATTR_CHANNEL_ID ; 
 size_t NCSI_ATTR_DATA ; 
 size_t NCSI_ATTR_IFINDEX ; 
 size_t NCSI_ATTR_PACKAGE_ID ; 
 scalar_t__ NCSI_MAX_CHANNEL ; 
 scalar_t__ NCSI_MAX_PACKAGE ; 
 int /*<<< orphan*/  NCSI_REQ_FLAG_NETLINK_DRIVEN ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_send_netlink_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ncsi_xmit_cmd (struct ncsi_cmd_arg*) ; 
 struct ncsi_dev_priv* ndp_from_ifindex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ nla_data (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (int /*<<< orphan*/ ) ; 
 int nla_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_send_cmd_nl(struct sk_buff *msg, struct genl_info *info)
{
	struct ncsi_dev_priv *ndp;
	struct ncsi_pkt_hdr *hdr;
	struct ncsi_cmd_arg nca;
	unsigned char *data;
	u32 package_id;
	u32 channel_id;
	int len, ret;

	if (!info || !info->attrs) {
		ret = -EINVAL;
		goto out;
	}

	if (!info->attrs[NCSI_ATTR_IFINDEX]) {
		ret = -EINVAL;
		goto out;
	}

	if (!info->attrs[NCSI_ATTR_PACKAGE_ID]) {
		ret = -EINVAL;
		goto out;
	}

	if (!info->attrs[NCSI_ATTR_CHANNEL_ID]) {
		ret = -EINVAL;
		goto out;
	}

	if (!info->attrs[NCSI_ATTR_DATA]) {
		ret = -EINVAL;
		goto out;
	}

	ndp = ndp_from_ifindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	if (!ndp) {
		ret = -ENODEV;
		goto out;
	}

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);
	channel_id = nla_get_u32(info->attrs[NCSI_ATTR_CHANNEL_ID]);

	if (package_id >= NCSI_MAX_PACKAGE || channel_id >= NCSI_MAX_CHANNEL) {
		ret = -ERANGE;
		goto out_netlink;
	}

	len = nla_len(info->attrs[NCSI_ATTR_DATA]);
	if (len < sizeof(struct ncsi_pkt_hdr)) {
		netdev_info(ndp->ndev.dev, "NCSI: no command to send %u\n",
			    package_id);
		ret = -EINVAL;
		goto out_netlink;
	} else {
		data = (unsigned char *)nla_data(info->attrs[NCSI_ATTR_DATA]);
	}

	hdr = (struct ncsi_pkt_hdr *)data;

	nca.ndp = ndp;
	nca.package = (unsigned char)package_id;
	nca.channel = (unsigned char)channel_id;
	nca.type = hdr->type;
	nca.req_flags = NCSI_REQ_FLAG_NETLINK_DRIVEN;
	nca.info = info;
	nca.payload = ntohs(hdr->length);
	nca.data = data + sizeof(*hdr);

	ret = ncsi_xmit_cmd(&nca);
out_netlink:
	if (ret != 0) {
		netdev_err(ndp->ndev.dev,
			   "NCSI: Error %d sending command\n",
			   ret);
		ncsi_send_netlink_err(ndp->ndev.dev,
				      info->snd_seq,
				      info->snd_portid,
				      info->nlhdr,
				      ret);
	}
out:
	return ret;
}