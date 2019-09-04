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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ poll_req_portid; int /*<<< orphan*/  genl_data_mutex; } ;
struct nfc_dev {TYPE_1__ genl_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  polling; } ;
struct genl_info {scalar_t__ snd_portid; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_put_device (struct nfc_dev*) ; 
 int nfc_stop_poll (struct nfc_dev*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_genl_stop_poll(struct sk_buff *skb, struct genl_info *info)
{
	struct nfc_dev *dev;
	int rc;
	u32 idx;

	if (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		return -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		return -ENODEV;

	device_lock(&dev->dev);

	if (!dev->polling) {
		device_unlock(&dev->dev);
		return -EINVAL;
	}

	device_unlock(&dev->dev);

	mutex_lock(&dev->genl_data.genl_data_mutex);

	if (dev->genl_data.poll_req_portid != info->snd_portid) {
		rc = -EBUSY;
		goto out;
	}

	rc = nfc_stop_poll(dev);
	dev->genl_data.poll_req_portid = 0;

out:
	mutex_unlock(&dev->genl_data.genl_data_mutex);
	nfc_put_device(dev);
	return rc;
}