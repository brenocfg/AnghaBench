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
struct wimax_dev {int dummy; } ;
struct sk_buff {size_t len; void* data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  d_dump (int,struct device*,void*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 int /*<<< orphan*/  genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_gnl_family ; 

int wimax_msg_send(struct wimax_dev *wimax_dev, struct sk_buff *skb)
{
	struct device *dev = wimax_dev_to_dev(wimax_dev);
	void *msg = skb->data;
	size_t size = skb->len;
	might_sleep();

	d_printf(1, dev, "CTX: wimax msg, %zu bytes\n", size);
	d_dump(2, dev, msg, size);
	genlmsg_multicast(&wimax_gnl_family, skb, 0, 0, GFP_KERNEL);
	d_printf(1, dev, "CTX: genl multicast done\n");
	return 0;
}