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
struct tcmu_dev {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCMU_ATTR_DEV_CFG ; 
 int /*<<< orphan*/  TCMU_CMD_RECONFIG_DEVICE ; 
 int nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int tcmu_netlink_event_init (struct tcmu_dev*,int /*<<< orphan*/ ,struct sk_buff**,void**) ; 
 int tcmu_netlink_event_send (struct tcmu_dev*,int /*<<< orphan*/ ,struct sk_buff*,void*) ; 

__attribute__((used)) static int tcmu_send_dev_config_event(struct tcmu_dev *udev,
				      const char *reconfig_data)
{
	struct sk_buff *skb = NULL;
	void *msg_header = NULL;
	int ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_RECONFIG_DEVICE,
				      &skb, &msg_header);
	if (ret < 0)
		return ret;
	ret = nla_put_string(skb, TCMU_ATTR_DEV_CFG, reconfig_data);
	if (ret < 0) {
		nlmsg_free(skb);
		return ret;
	}
	return tcmu_netlink_event_send(udev, TCMU_CMD_RECONFIG_DEVICE,
				       skb, msg_header);
}