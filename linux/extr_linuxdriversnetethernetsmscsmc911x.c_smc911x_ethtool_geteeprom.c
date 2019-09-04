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
struct ethtool_eeprom {int offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD_EPC_CMD_READ_ ; 
 int SMC911X_EEPROM_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int smc911x_ethtool_read_eeprom_byte (struct net_device*,int /*<<< orphan*/ *) ; 
 int smc911x_ethtool_write_eeprom_cmd (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smc911x_ethtool_geteeprom(struct net_device *dev,
									  struct ethtool_eeprom *eeprom, u8 *data)
{
	u8 eebuf[SMC911X_EEPROM_LEN];
	int i, ret;

	for(i=0;i<SMC911X_EEPROM_LEN;i++) {
		if ((ret=smc911x_ethtool_write_eeprom_cmd(dev, E2P_CMD_EPC_CMD_READ_, i ))!=0)
			return ret;
		if ((ret=smc911x_ethtool_read_eeprom_byte(dev, &eebuf[i]))!=0)
			return ret;
		}
	memcpy(data, eebuf+eeprom->offset, eeprom->len);
	return 0;
}