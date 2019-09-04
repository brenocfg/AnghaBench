#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; struct airo_info* ml_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  macAddr; } ;
struct airo_info {TYPE_3__* wifidev; TYPE_2__* dev; int /*<<< orphan*/  flags; TYPE_1__ config; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_COMMIT ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readConfigRid (struct airo_info*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeConfigRid (struct airo_info*,int) ; 

__attribute__((used)) static int airo_set_mac_address(struct net_device *dev, void *p)
{
	struct airo_info *ai = dev->ml_priv;
	struct sockaddr *addr = p;

	readConfigRid(ai, 1);
	memcpy (ai->config.macAddr, addr->sa_data, dev->addr_len);
	set_bit (FLAG_COMMIT, &ai->flags);
	disable_MAC(ai, 1);
	writeConfigRid (ai, 1);
	enable_MAC(ai, 1);
	memcpy (ai->dev->dev_addr, addr->sa_data, dev->addr_len);
	if (ai->wifidev)
		memcpy (ai->wifidev->dev_addr, addr->sa_data, dev->addr_len);
	return 0;
}