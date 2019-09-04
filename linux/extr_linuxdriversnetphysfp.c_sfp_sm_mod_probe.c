#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int diagmon; int /*<<< orphan*/  phys_ext_id; int /*<<< orphan*/  phys_id; int /*<<< orphan*/  datecode; int /*<<< orphan*/  vendor_sn; int /*<<< orphan*/  vendor_rev; int /*<<< orphan*/  vendor_pn; int /*<<< orphan*/  vendor_name; int /*<<< orphan*/  cc_ext; int /*<<< orphan*/  cc_base; } ;
struct sfp_eeprom_id {TYPE_2__ ext; TYPE_2__ base; } ;
struct sfp {struct sfp_eeprom_id id; int /*<<< orphan*/  sfp_bus; int /*<<< orphan*/  dev; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_4__ {int /*<<< orphan*/  (* module_supported ) (struct sfp_eeprom_id*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SFP_DIAGMON_ADDRMODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct sfp_eeprom_id*,int,int) ; 
 int /*<<< orphan*/  sfp_check (TYPE_2__*,int) ; 
 int sfp_hwmon_insert (struct sfp*) ; 
 int sfp_module_insert (int /*<<< orphan*/ ,struct sfp_eeprom_id*) ; 
 int sfp_read (struct sfp*,int,int /*<<< orphan*/ ,struct sfp_eeprom_id*,int) ; 
 int sfp_sm_mod_hpower (struct sfp*) ; 
 int /*<<< orphan*/  stub1 (struct sfp_eeprom_id*) ; 

__attribute__((used)) static int sfp_sm_mod_probe(struct sfp *sfp)
{
	/* SFP module inserted - read I2C data */
	struct sfp_eeprom_id id;
	bool cotsworks;
	u8 check;
	int ret;

	ret = sfp_read(sfp, false, 0, &id, sizeof(id));
	if (ret < 0) {
		dev_err(sfp->dev, "failed to read EEPROM: %d\n", ret);
		return -EAGAIN;
	}

	if (ret != sizeof(id)) {
		dev_err(sfp->dev, "EEPROM short read: %d\n", ret);
		return -EAGAIN;
	}

	/* Cotsworks do not seem to update the checksums when they
	 * do the final programming with the final module part number,
	 * serial number and date code.
	 */
	cotsworks = !memcmp(id.base.vendor_name, "COTSWORKS       ", 16);

	/* Validate the checksum over the base structure */
	check = sfp_check(&id.base, sizeof(id.base) - 1);
	if (check != id.base.cc_base) {
		if (cotsworks) {
			dev_warn(sfp->dev,
				 "EEPROM base structure checksum failure (0x%02x != 0x%02x)\n",
				 check, id.base.cc_base);
		} else {
			dev_err(sfp->dev,
				"EEPROM base structure checksum failure: 0x%02x != 0x%02x\n",
				check, id.base.cc_base);
			print_hex_dump(KERN_ERR, "sfp EE: ", DUMP_PREFIX_OFFSET,
				       16, 1, &id, sizeof(id), true);
			return -EINVAL;
		}
	}

	check = sfp_check(&id.ext, sizeof(id.ext) - 1);
	if (check != id.ext.cc_ext) {
		if (cotsworks) {
			dev_warn(sfp->dev,
				 "EEPROM extended structure checksum failure (0x%02x != 0x%02x)\n",
				 check, id.ext.cc_ext);
		} else {
			dev_err(sfp->dev,
				"EEPROM extended structure checksum failure: 0x%02x != 0x%02x\n",
				check, id.ext.cc_ext);
			print_hex_dump(KERN_ERR, "sfp EE: ", DUMP_PREFIX_OFFSET,
				       16, 1, &id, sizeof(id), true);
			memset(&id.ext, 0, sizeof(id.ext));
		}
	}

	sfp->id = id;

	dev_info(sfp->dev, "module %.*s %.*s rev %.*s sn %.*s dc %.*s\n",
		 (int)sizeof(id.base.vendor_name), id.base.vendor_name,
		 (int)sizeof(id.base.vendor_pn), id.base.vendor_pn,
		 (int)sizeof(id.base.vendor_rev), id.base.vendor_rev,
		 (int)sizeof(id.ext.vendor_sn), id.ext.vendor_sn,
		 (int)sizeof(id.ext.datecode), id.ext.datecode);

	/* Check whether we support this module */
	if (!sfp->type->module_supported(&sfp->id)) {
		dev_err(sfp->dev,
			"module is not supported - phys id 0x%02x 0x%02x\n",
			sfp->id.base.phys_id, sfp->id.base.phys_ext_id);
		return -EINVAL;
	}

	/* If the module requires address swap mode, warn about it */
	if (sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE)
		dev_warn(sfp->dev,
			 "module address swap to access page 0xA2 is not supported.\n");

	ret = sfp_hwmon_insert(sfp);
	if (ret < 0)
		return ret;

	ret = sfp_module_insert(sfp->sfp_bus, &sfp->id);
	if (ret < 0)
		return ret;

	return sfp_sm_mod_hpower(sfp);
}