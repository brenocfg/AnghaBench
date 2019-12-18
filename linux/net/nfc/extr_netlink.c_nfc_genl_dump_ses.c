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
struct sk_buff {int len; } ;
struct nfc_dev {int dummy; } ;
struct netlink_callback {long* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; } ;
struct class_dev_iter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct class_dev_iter* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_device_iter_init (struct class_dev_iter*) ; 
 struct nfc_dev* nfc_device_iter_next (struct class_dev_iter*) ; 
 int /*<<< orphan*/  nfc_devlist_generation ; 
 int /*<<< orphan*/  nfc_devlist_mutex ; 
 int nfc_genl_send_se (struct sk_buff*,struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_callback*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_dump_ses(struct sk_buff *skb,
				 struct netlink_callback *cb)
{
	struct class_dev_iter *iter = (struct class_dev_iter *) cb->args[0];
	struct nfc_dev *dev = (struct nfc_dev *) cb->args[1];
	bool first_call = false;

	if (!iter) {
		first_call = true;
		iter = kmalloc(sizeof(struct class_dev_iter), GFP_KERNEL);
		if (!iter)
			return -ENOMEM;
		cb->args[0] = (long) iter;
	}

	mutex_lock(&nfc_devlist_mutex);

	cb->seq = nfc_devlist_generation;

	if (first_call) {
		nfc_device_iter_init(iter);
		dev = nfc_device_iter_next(iter);
	}

	while (dev) {
		int rc;

		rc = nfc_genl_send_se(skb, dev, NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, cb, NLM_F_MULTI);
		if (rc < 0)
			break;

		dev = nfc_device_iter_next(iter);
	}

	mutex_unlock(&nfc_devlist_mutex);

	cb->args[1] = (long) dev;

	return skb->len;
}