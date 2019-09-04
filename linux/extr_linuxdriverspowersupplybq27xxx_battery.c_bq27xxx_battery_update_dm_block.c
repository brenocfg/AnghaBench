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
struct bq27xxx_dm_reg {int bytes; } ;
struct bq27xxx_dm_buf {int dirty; int /*<<< orphan*/  has_data; } ;
struct bq27xxx_device_info {int opts; int /*<<< orphan*/  dev; struct bq27xxx_dm_reg* dm_regs; } ;
typedef  enum bq27xxx_dm_reg_id { ____Placeholder_bq27xxx_dm_reg_id } bq27xxx_dm_reg_id ;

/* Variables and functions */
 int BQ27XXX_O_RAM ; 
 unsigned int be16_to_cpup (int /*<<< orphan*/ *) ; 
 char** bq27xxx_dm_reg_name ; 
 int /*<<< orphan*/ * bq27xxx_dm_reg_ptr (struct bq27xxx_dm_buf*,struct bq27xxx_dm_reg*) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void bq27xxx_battery_update_dm_block(struct bq27xxx_device_info *di,
					    struct bq27xxx_dm_buf *buf,
					    enum bq27xxx_dm_reg_id reg_id,
					    unsigned int val)
{
	struct bq27xxx_dm_reg *reg = &di->dm_regs[reg_id];
	const char *str = bq27xxx_dm_reg_name[reg_id];
	u16 *prev = bq27xxx_dm_reg_ptr(buf, reg);

	if (prev == NULL) {
		dev_warn(di->dev, "buffer does not match %s dm spec\n", str);
		return;
	}

	if (reg->bytes != 2) {
		dev_warn(di->dev, "%s dm spec has unsupported byte size\n", str);
		return;
	}

	if (!buf->has_data)
		return;

	if (be16_to_cpup(prev) == val) {
		dev_info(di->dev, "%s has %u\n", str, val);
		return;
	}

#ifdef CONFIG_BATTERY_BQ27XXX_DT_UPDATES_NVM
	if (!(di->opts & BQ27XXX_O_RAM) && !bq27xxx_dt_to_nvm) {
#else
	if (!(di->opts & BQ27XXX_O_RAM)) {
#endif
		/* devicetree and NVM differ; defer to NVM */
		dev_warn(di->dev, "%s has %u; update to %u disallowed "
#ifdef CONFIG_BATTERY_BQ27XXX_DT_UPDATES_NVM
			 "by dt_monitored_battery_updates_nvm=0"
#else
			 "for flash/NVM data memory"
#endif
			 "\n", str, be16_to_cpup(prev), val);
		return;
	}

	dev_info(di->dev, "update %s to %u\n", str, val);

	*prev = cpu_to_be16(val);
	buf->dirty = true;
}