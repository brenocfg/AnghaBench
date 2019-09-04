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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  CONFIG_IOSF_MBI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  iosf_mbi_available () ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  is_byt () ; 

__attribute__((used)) static int is_byt_cr(struct device *dev, bool *bytcr)
{
	int status = 0;

	if (IS_ENABLED(CONFIG_IOSF_MBI)) {
		u32 bios_status;

		if (!is_byt() || !iosf_mbi_available()) {
			/* bail silently */
			return status;
		}

		status = iosf_mbi_read(BT_MBI_UNIT_PMC, /* 0x04 PUNIT */
				       MBI_REG_READ, /* 0x10 */
				       0x006, /* BIOS_CONFIG */
				       &bios_status);

		if (status) {
			dev_err(dev, "could not read PUNIT BIOS_CONFIG\n");
		} else {
			/* bits 26:27 mirror PMIC options */
			bios_status = (bios_status >> 26) & 3;

			if ((bios_status == 1) || (bios_status == 3))
				*bytcr = true;
			else
				dev_info(dev, "BYT-CR not detected\n");
		}
	} else {
		dev_info(dev, "IOSF_MBI not enabled, no BYT-CR detection\n");
	}
	return status;
}