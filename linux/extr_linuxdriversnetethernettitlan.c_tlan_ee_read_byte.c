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
struct tlan_priv {int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_EEPROM_ACK ; 
 int /*<<< orphan*/  TLAN_EEPROM_STOP ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlan_ee_receive_byte (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int tlan_ee_send_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_ee_send_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlan_ee_read_byte(struct net_device *dev, u8 ee_addr, u8 *data)
{
	int err;
	struct tlan_priv *priv = netdev_priv(dev);
	unsigned long flags = 0;
	int ret = 0;

	spin_lock_irqsave(&priv->lock, flags);

	tlan_ee_send_start(dev->base_addr);
	err = tlan_ee_send_byte(dev->base_addr, 0xa0, TLAN_EEPROM_ACK);
	if (err) {
		ret = 1;
		goto fail;
	}
	err = tlan_ee_send_byte(dev->base_addr, ee_addr, TLAN_EEPROM_ACK);
	if (err) {
		ret = 2;
		goto fail;
	}
	tlan_ee_send_start(dev->base_addr);
	err = tlan_ee_send_byte(dev->base_addr, 0xa1, TLAN_EEPROM_ACK);
	if (err) {
		ret = 3;
		goto fail;
	}
	tlan_ee_receive_byte(dev->base_addr, data, TLAN_EEPROM_STOP);
fail:
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;

}