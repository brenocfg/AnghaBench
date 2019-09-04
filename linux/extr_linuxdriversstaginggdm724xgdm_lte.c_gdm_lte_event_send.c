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
struct phy_dev {int /*<<< orphan*/  priv_dev; int /*<<< orphan*/  (* get_endian ) (int /*<<< orphan*/ ) ;} ;
struct nic {struct phy_dev* phy_dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct hci_packet {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int EINVAL ; 
 int HCI_HEADER_SIZE ; 
 int gdm_dev16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ lte_event ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int netlink_send (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdm_lte_event_send(struct net_device *dev, char *buf, int len)
{
	struct phy_dev *phy_dev = ((struct nic *)netdev_priv(dev))->phy_dev;
	struct hci_packet *hci = (struct hci_packet *)buf;
	int length;
	int idx;
	int ret;

	ret = sscanf(dev->name, "lte%d", &idx);
	if (ret != 1)
		return -EINVAL;

	length = gdm_dev16_to_cpu(phy_dev->get_endian(phy_dev->priv_dev),
				  hci->len) + HCI_HEADER_SIZE;
	return netlink_send(lte_event.sock, idx, 0, buf, length);
}