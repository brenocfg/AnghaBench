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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  __bdx_vlan_rx_vid (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bdx_vlan_rx_add_vid(struct net_device *ndev, __be16 proto, u16 vid)
{
	__bdx_vlan_rx_vid(ndev, vid, 1);
	return 0;
}