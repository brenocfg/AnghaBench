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
struct ethtool_eeprom {int offset; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD_EPC_CMD_ERASE_ ; 
 int /*<<< orphan*/  E2P_CMD_EPC_CMD_EWEN_ ; 
 int /*<<< orphan*/  E2P_CMD_EPC_CMD_WRITE_ ; 
 int smc911x_ethtool_write_eeprom_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int smc911x_ethtool_write_eeprom_cmd (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smc911x_ethtool_seteeprom(struct net_device *dev,
									   struct ethtool_eeprom *eeprom, u8 *data)
{
	int i, ret;

	/* Enable erase */
	if ((ret=smc911x_ethtool_write_eeprom_cmd(dev, E2P_CMD_EPC_CMD_EWEN_, 0 ))!=0)
		return ret;
	for(i=eeprom->offset;i<(eeprom->offset+eeprom->len);i++) {
		/* erase byte */
		if ((ret=smc911x_ethtool_write_eeprom_cmd(dev, E2P_CMD_EPC_CMD_ERASE_, i ))!=0)
			return ret;
		/* write byte */
		if ((ret=smc911x_ethtool_write_eeprom_byte(dev, *data))!=0)
			 return ret;
		if ((ret=smc911x_ethtool_write_eeprom_cmd(dev, E2P_CMD_EPC_CMD_WRITE_, i ))!=0)
			return ret;
		}
	 return 0;
}