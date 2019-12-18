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
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {struct switch_val* link; int /*<<< orphan*/  s; int /*<<< orphan*/  i; struct switch_val* ports; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_port_link {int dummy; } ;
struct switch_port {int dummy; } ;
struct switch_dev {int ports; struct switch_val linkbuf; struct switch_val* portbuf; } ;
struct switch_attr {int (* get ) (struct switch_dev*,struct switch_attr const*,struct switch_val*) ;int type; } ;
struct sk_buff {int len; } ;
struct genlmsghdr {int cmd; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  nlhdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct genlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VALUE_INT ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VALUE_LINK ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VALUE_PORTS ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VALUE_STR ; 
#define  SWITCH_TYPE_INT 131 
#define  SWITCH_TYPE_LINK 130 
#define  SWITCH_TYPE_PORTS 129 
#define  SWITCH_TYPE_STRING 128 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct genlmsghdr*) ; 
 struct genlmsghdr* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  memset (struct switch_val*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int stub1 (struct switch_dev*,struct switch_attr const*,struct switch_val*) ; 
 struct switch_dev* swconfig_get_dev (struct genl_info*) ; 
 struct switch_attr* swconfig_lookup_attr (struct switch_dev*,struct genl_info*,struct switch_val*) ; 
 int /*<<< orphan*/  swconfig_put_dev (struct switch_dev*) ; 
 int swconfig_send_link (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ,struct switch_val*) ; 
 int swconfig_send_ports (struct sk_buff**,struct genl_info*,int /*<<< orphan*/ ,struct switch_val*) ; 
 int /*<<< orphan*/  switch_fam ; 

__attribute__((used)) static int
swconfig_get_attr(struct sk_buff *skb, struct genl_info *info)
{
	struct genlmsghdr *hdr = nlmsg_data(info->nlhdr);
	const struct switch_attr *attr;
	struct switch_dev *dev;
	struct sk_buff *msg = NULL;
	struct switch_val val;
	int err = -EINVAL;
	int cmd = hdr->cmd;

	dev = swconfig_get_dev(info);
	if (!dev)
		return -EINVAL;

	memset(&val, 0, sizeof(val));
	attr = swconfig_lookup_attr(dev, info, &val);
	if (!attr || !attr->get)
		goto error;

	if (attr->type == SWITCH_TYPE_PORTS) {
		val.value.ports = dev->portbuf;
		memset(dev->portbuf, 0,
			sizeof(struct switch_port) * dev->ports);
	} else if (attr->type == SWITCH_TYPE_LINK) {
		val.value.link = &dev->linkbuf;
		memset(&dev->linkbuf, 0, sizeof(struct switch_port_link));
	}

	err = attr->get(dev, attr, &val);
	if (err)
		goto error;

	msg = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!msg)
		goto error;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq, &switch_fam,
			0, cmd);
	if (IS_ERR(hdr))
		goto nla_put_failure;

	switch (attr->type) {
	case SWITCH_TYPE_INT:
		if (nla_put_u32(msg, SWITCH_ATTR_OP_VALUE_INT, val.value.i))
			goto nla_put_failure;
		break;
	case SWITCH_TYPE_STRING:
		if (nla_put_string(msg, SWITCH_ATTR_OP_VALUE_STR, val.value.s))
			goto nla_put_failure;
		break;
	case SWITCH_TYPE_PORTS:
		err = swconfig_send_ports(&msg, info,
				SWITCH_ATTR_OP_VALUE_PORTS, &val);
		if (err < 0)
			goto nla_put_failure;
		break;
	case SWITCH_TYPE_LINK:
		err = swconfig_send_link(msg, info,
					 SWITCH_ATTR_OP_VALUE_LINK, val.value.link);
		if (err < 0)
			goto nla_put_failure;
		break;
	default:
		pr_debug("invalid type in attribute\n");
		err = -EINVAL;
		goto nla_put_failure;
	}
	genlmsg_end(msg, hdr);
	err = msg->len;
	if (err < 0)
		goto nla_put_failure;

	swconfig_put_dev(dev);
	return genlmsg_reply(msg, info);

nla_put_failure:
	if (msg)
		nlmsg_free(msg);
error:
	swconfig_put_dev(dev);
	if (!err)
		err = -ENOMEM;
	return err;
}