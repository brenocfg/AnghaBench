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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  blank ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sh_eth_tsu_find_entry (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh_eth_tsu_find_empty(struct net_device *ndev)
{
	u8 blank[ETH_ALEN];
	int entry;

	memset(blank, 0, sizeof(blank));
	entry = sh_eth_tsu_find_entry(ndev, blank);
	return (entry < 0) ? -ENOMEM : entry;
}