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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cas {int pause_last_time_recvd; int /*<<< orphan*/  pause_entered; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MAC_CTRL_PAUSE_RECEIVED ; 
 int MAC_CTRL_PAUSE_STATE ; 
 scalar_t__ REG_MAC_CTRL_STATUS ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int cas_mac_interrupt(struct net_device *dev, struct cas *cp,
			     u32 status)
{
	u32 stat = readl(cp->regs + REG_MAC_CTRL_STATUS);

	if (!stat)
		return 0;

	netif_printk(cp, intr, KERN_DEBUG, cp->dev,
		     "mac interrupt, stat: 0x%x\n", stat);

	/* This interrupt is just for pause frame and pause
	 * tracking.  It is useful for diagnostics and debug
	 * but probably by default we will mask these events.
	 */
	if (stat & MAC_CTRL_PAUSE_STATE)
		cp->pause_entered++;

	if (stat & MAC_CTRL_PAUSE_RECEIVED)
		cp->pause_last_time_recvd = (stat >> 16);

	return 0;
}