#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct il_priv {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ eeprom_ver; scalar_t__ eeprom_calib_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_4965_CALIB_VERSION_OFFSET ; 
 int /*<<< orphan*/  EEPROM_VERSION ; 
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IL_INFO (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ il_eeprom_query16 (struct il_priv*,int /*<<< orphan*/ ) ; 

int
il4965_eeprom_check_version(struct il_priv *il)
{
	u16 eeprom_ver;
	u16 calib_ver;

	eeprom_ver = il_eeprom_query16(il, EEPROM_VERSION);
	calib_ver = il_eeprom_query16(il, EEPROM_4965_CALIB_VERSION_OFFSET);

	if (eeprom_ver < il->cfg->eeprom_ver ||
	    calib_ver < il->cfg->eeprom_calib_ver)
		goto err;

	IL_INFO("device EEPROM VER=0x%x, CALIB=0x%x\n", eeprom_ver, calib_ver);

	return 0;
err:
	IL_ERR("Unsupported (too old) EEPROM VER=0x%x < 0x%x "
	       "CALIB=0x%x < 0x%x\n", eeprom_ver, il->cfg->eeprom_ver,
	       calib_ver, il->cfg->eeprom_calib_ver);
	return -EINVAL;

}