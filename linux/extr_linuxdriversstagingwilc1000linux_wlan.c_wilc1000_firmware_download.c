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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {TYPE_1__* firmware; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int wilc_wlan_firmware_download (struct wilc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc1000_firmware_download(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;
	int ret = 0;

	if (!wilc->firmware) {
		netdev_err(dev, "Firmware buffer is NULL\n");
		return -ENOBUFS;
	}

	ret = wilc_wlan_firmware_download(wilc, wilc->firmware->data,
					  wilc->firmware->size);
	if (ret < 0)
		return ret;

	release_firmware(wilc->firmware);
	wilc->firmware = NULL;

	netdev_dbg(dev, "Download Succeeded\n");

	return 0;
}