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
struct tsi108_prv_data {int /*<<< orphan*/  misclock; int /*<<< orphan*/  txlock; scalar_t__ link_up; scalar_t__ txfree; } ;
struct net_device {unsigned char* dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  TSI108_MAC_ADDR1 ; 
 int /*<<< orphan*/  TSI108_MAC_ADDR2 ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (void*) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsi108_set_mac(struct net_device *dev, void *addr)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	u32 word1, word2;
	int i;

	if (!is_valid_ether_addr(addr))
		return -EADDRNOTAVAIL;

	for (i = 0; i < 6; i++)
		/* +2 is for the offset of the HW addr type */
		dev->dev_addr[i] = ((unsigned char *)addr)[i + 2];

	word2 = (dev->dev_addr[0] << 16) | (dev->dev_addr[1] << 24);

	word1 = (dev->dev_addr[2] << 0) | (dev->dev_addr[3] << 8) |
	    (dev->dev_addr[4] << 16) | (dev->dev_addr[5] << 24);

	spin_lock_irq(&data->misclock);
	TSI_WRITE(TSI108_MAC_ADDR1, word1);
	TSI_WRITE(TSI108_MAC_ADDR2, word2);
	spin_lock(&data->txlock);

	if (data->txfree && data->link_up)
		netif_wake_queue(dev);

	spin_unlock(&data->txlock);
	spin_unlock_irq(&data->misclock);
	return 0;
}