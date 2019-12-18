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
typedef  int u8 ;
struct net_device {int addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
#define  ETH_ALEN 129 
#define  EUI64_ADDR_LEN 128 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int addrconf_ifid_6lowpan(u8 *eui, struct net_device *dev)
{
	switch (dev->addr_len) {
	case ETH_ALEN:
		memcpy(eui, dev->dev_addr, 3);
		eui[3] = 0xFF;
		eui[4] = 0xFE;
		memcpy(eui + 5, dev->dev_addr + 3, 3);
		break;
	case EUI64_ADDR_LEN:
		memcpy(eui, dev->dev_addr, EUI64_ADDR_LEN);
		eui[0] ^= 2;
		break;
	default:
		return -1;
	}

	return 0;
}