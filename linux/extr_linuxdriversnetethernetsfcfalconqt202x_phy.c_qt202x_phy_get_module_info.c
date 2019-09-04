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
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 

__attribute__((used)) static int qt202x_phy_get_module_info(struct ef4_nic *efx,
				      struct ethtool_modinfo *modinfo)
{
	modinfo->type = ETH_MODULE_SFF_8079;
	modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	return 0;
}