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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int INTEGRATOR_CM_CTRL_RESET ; 
 int /*<<< orphan*/  INTEGRATOR_HDR_CTRL_OFFSET ; 
 int /*<<< orphan*/  INTEGRATOR_HDR_LOCK_OFFSET ; 
#define  INTEGRATOR_REBOOT_CM 134 
 int NOTIFY_DONE ; 
#define  REALVIEW_REBOOT_EB 133 
#define  REALVIEW_REBOOT_PB1176 132 
#define  REALVIEW_REBOOT_PB11MP 131 
#define  REALVIEW_REBOOT_PBA8 130 
#define  REALVIEW_REBOOT_PBX 129 
 int VERSATILE_LOCK_VAL ; 
#define  VERSATILE_REBOOT_CM 128 
 int /*<<< orphan*/  VERSATILE_SYS_LOCK_OFFSET ; 
 int /*<<< orphan*/  VERSATILE_SYS_RESETCTL_OFFSET ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscon_regmap ; 
 int versatile_reboot_type ; 

__attribute__((used)) static int versatile_reboot(struct notifier_block *this, unsigned long mode,
			    void *cmd)
{
	/* Unlock the reset register */
	/* Then hit reset on the different machines */
	switch (versatile_reboot_type) {
	case INTEGRATOR_REBOOT_CM:
		regmap_write(syscon_regmap, INTEGRATOR_HDR_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_update_bits(syscon_regmap,
				   INTEGRATOR_HDR_CTRL_OFFSET,
				   INTEGRATOR_CM_CTRL_RESET,
				   INTEGRATOR_CM_CTRL_RESET);
		break;
	case VERSATILE_REBOOT_CM:
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_update_bits(syscon_regmap,
				   VERSATILE_SYS_RESETCTL_OFFSET,
				   0x0107,
				   0x0105);
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     0);
		break;
	case REALVIEW_REBOOT_EB:
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_write(syscon_regmap,
			     VERSATILE_SYS_RESETCTL_OFFSET, 0x0008);
		break;
	case REALVIEW_REBOOT_PB1176:
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_write(syscon_regmap,
			     VERSATILE_SYS_RESETCTL_OFFSET, 0x0100);
		break;
	case REALVIEW_REBOOT_PB11MP:
	case REALVIEW_REBOOT_PBA8:
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_write(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x0000);
		regmap_write(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x0004);
		break;
	case REALVIEW_REBOOT_PBX:
		regmap_write(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_write(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x00f0);
		regmap_write(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x00f4);
		break;
	}
	dsb();

	return NOTIFY_DONE;
}