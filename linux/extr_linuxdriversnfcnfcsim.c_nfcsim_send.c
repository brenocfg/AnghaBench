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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfcsim {int /*<<< orphan*/  send_work; int /*<<< orphan*/  mode; int /*<<< orphan*/  rf_tech; int /*<<< orphan*/  link_out; scalar_t__ dropframe; int /*<<< orphan*/  recv_work; void* arg; int /*<<< orphan*/  cb; int /*<<< orphan*/  recv_timeout; int /*<<< orphan*/  up; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NFCSIM_DBG (struct nfcsim*,char*,scalar_t__) ; 
 int /*<<< orphan*/  NFCSIM_ERR (struct nfcsim*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct nfcsim* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  nfcsim_link_set_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfcsim_send(struct nfc_digital_dev *ddev, struct sk_buff *skb,
		       u16 timeout, nfc_digital_cmd_complete_t cb, void *arg)
{
	struct nfcsim *dev = nfc_digital_get_drvdata(ddev);
	u8 delay;

	if (!dev->up) {
		NFCSIM_ERR(dev, "Device is down\n");
		return -ENODEV;
	}

	dev->recv_timeout = timeout;
	dev->cb = cb;
	dev->arg = arg;

	schedule_work(&dev->recv_work);

	if (dev->dropframe) {
		NFCSIM_DBG(dev, "dropping frame (out of %d)\n", dev->dropframe);
		dev_kfree_skb(skb);
		dev->dropframe--;

		return 0;
	}

	if (skb) {
		nfcsim_link_set_skb(dev->link_out, skb, dev->rf_tech,
				    dev->mode);

		/* Add random delay (between 3 and 10 ms) before sending data */
		get_random_bytes(&delay, 1);
		delay = 3 + (delay & 0x07);

		schedule_delayed_work(&dev->send_work, msecs_to_jiffies(delay));
	}

	return 0;
}