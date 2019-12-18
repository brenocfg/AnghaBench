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
struct sk_buff {int len; } ;
struct nfc_dev {int n_targets; int /*<<< orphan*/  dev; int /*<<< orphan*/ * targets; int /*<<< orphan*/  targets_generation; } ;
struct netlink_callback {int* args; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfc_dev*) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int PTR_ERR (struct nfc_dev*) ; 
 struct nfc_dev* __get_device_from_cb (struct netlink_callback*) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int nfc_genl_send_target (struct sk_buff*,int /*<<< orphan*/ *,struct netlink_callback*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_dump_targets(struct sk_buff *skb,
				 struct netlink_callback *cb)
{
	int i = cb->args[0];
	struct nfc_dev *dev = (struct nfc_dev *) cb->args[1];
	int rc;

	if (!dev) {
		dev = __get_device_from_cb(cb);
		if (IS_ERR(dev))
			return PTR_ERR(dev);

		cb->args[1] = (long) dev;
	}

	device_lock(&dev->dev);

	cb->seq = dev->targets_generation;

	while (i < dev->n_targets) {
		rc = nfc_genl_send_target(skb, &dev->targets[i], cb,
					  NLM_F_MULTI);
		if (rc < 0)
			break;

		i++;
	}

	device_unlock(&dev->dev);

	cb->args[0] = i;

	return skb->len;
}