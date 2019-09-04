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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ sh_eth_read (struct net_device*,int) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sh_eth_update_stat(struct net_device *ndev, unsigned long *stat, int reg)
{
	u32 delta = sh_eth_read(ndev, reg);

	if (delta) {
		*stat += delta;
		sh_eth_write(ndev, 0, reg);
	}
}