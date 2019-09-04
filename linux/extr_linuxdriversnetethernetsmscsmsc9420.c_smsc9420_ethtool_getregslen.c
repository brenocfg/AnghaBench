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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int smsc9420_ethtool_getregslen(struct net_device *dev)
{
	/* all smsc9420 registers plus all phy registers */
	return 0x100 + (32 * sizeof(u32));
}