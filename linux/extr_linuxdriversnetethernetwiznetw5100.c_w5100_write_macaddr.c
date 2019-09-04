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
struct w5100_priv {struct net_device* ndev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  W5100_SHAR ; 
 int /*<<< orphan*/  w5100_writebulk (struct w5100_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w5100_write_macaddr(struct w5100_priv *priv)
{
	struct net_device *ndev = priv->ndev;

	w5100_writebulk(priv, W5100_SHAR, ndev->dev_addr, ETH_ALEN);
}