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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sh_eth_private {TYPE_1__* cd; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TSU_ADRH0 ; 
 int /*<<< orphan*/  TSU_TEN ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_tsu_enable_cam_entry_post (struct net_device*,int) ; 
 int sh_eth_tsu_find_empty (struct net_device*) ; 
 int sh_eth_tsu_find_entry (struct net_device*,int /*<<< orphan*/  const*) ; 
 scalar_t__ sh_eth_tsu_get_offset (struct sh_eth_private*,int /*<<< orphan*/ ) ; 
 int sh_eth_tsu_read (struct sh_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_tsu_write (struct sh_eth_private*,int,int /*<<< orphan*/ ) ; 
 int sh_eth_tsu_write_entry (struct net_device*,scalar_t__,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int sh_eth_tsu_add_entry(struct net_device *ndev, const u8 *addr)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	int i, ret;

	if (!mdp->cd->tsu)
		return 0;

	i = sh_eth_tsu_find_entry(ndev, addr);
	if (i < 0) {
		/* No entry found, create one */
		i = sh_eth_tsu_find_empty(ndev);
		if (i < 0)
			return -ENOMEM;
		ret = sh_eth_tsu_write_entry(ndev, reg_offset + i * 8, addr);
		if (ret < 0)
			return ret;

		/* Enable the entry */
		sh_eth_tsu_write(mdp, sh_eth_tsu_read(mdp, TSU_TEN) |
				 (1 << (31 - i)), TSU_TEN);
	}

	/* Entry found or created, enable POST */
	sh_eth_tsu_enable_cam_entry_post(ndev, i);

	return 0;
}