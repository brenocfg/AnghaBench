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
typedef  int /*<<< orphan*/  u32 ;
struct sp5100_tco {int tco_reg_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFCH_PM_DECODEEN3 ; 
 int /*<<< orphan*/  EFCH_PM_DECODEEN_SECOND_RES ; 
 int EFCH_PM_WATCHDOG_DISABLE ; 
 int /*<<< orphan*/  SB800_PCI_WATCHDOG_DECODE_EN ; 
 int /*<<< orphan*/  SB800_PM_WATCHDOG_CONFIG ; 
 int /*<<< orphan*/  SB800_PM_WATCHDOG_CONTROL ; 
 int SB800_PM_WATCHDOG_DISABLE ; 
 int /*<<< orphan*/  SB800_PM_WATCHDOG_SECOND_RES ; 
 int /*<<< orphan*/  SP5100_PCI_WATCHDOG_DECODE_EN ; 
 int /*<<< orphan*/  SP5100_PCI_WATCHDOG_MISC_REG ; 
 int /*<<< orphan*/  SP5100_PM_WATCHDOG_CONTROL ; 
 int SP5100_PM_WATCHDOG_DISABLE ; 
 int /*<<< orphan*/  SP5100_PM_WATCHDOG_SECOND_RES ; 
#define  efch 130 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  sb800 129 
#define  sp5100 128 
 int /*<<< orphan*/  sp5100_tco_pci ; 
 int /*<<< orphan*/  sp5100_tco_update_pm_reg8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tco_timer_enable(struct sp5100_tco *tco)
{
	u32 val;

	switch (tco->tco_reg_layout) {
	case sb800:
		/* For SB800 or later */
		/* Set the Watchdog timer resolution to 1 sec */
		sp5100_tco_update_pm_reg8(SB800_PM_WATCHDOG_CONFIG,
					  0xff, SB800_PM_WATCHDOG_SECOND_RES);

		/* Enable watchdog decode bit and watchdog timer */
		sp5100_tco_update_pm_reg8(SB800_PM_WATCHDOG_CONTROL,
					  ~SB800_PM_WATCHDOG_DISABLE,
					  SB800_PCI_WATCHDOG_DECODE_EN);
		break;
	case sp5100:
		/* For SP5100 or SB7x0 */
		/* Enable watchdog decode bit */
		pci_read_config_dword(sp5100_tco_pci,
				      SP5100_PCI_WATCHDOG_MISC_REG,
				      &val);

		val |= SP5100_PCI_WATCHDOG_DECODE_EN;

		pci_write_config_dword(sp5100_tco_pci,
				       SP5100_PCI_WATCHDOG_MISC_REG,
				       val);

		/* Enable Watchdog timer and set the resolution to 1 sec */
		sp5100_tco_update_pm_reg8(SP5100_PM_WATCHDOG_CONTROL,
					  ~SP5100_PM_WATCHDOG_DISABLE,
					  SP5100_PM_WATCHDOG_SECOND_RES);
		break;
	case efch:
		/* Set the Watchdog timer resolution to 1 sec and enable */
		sp5100_tco_update_pm_reg8(EFCH_PM_DECODEEN3,
					  ~EFCH_PM_WATCHDOG_DISABLE,
					  EFCH_PM_DECODEEN_SECOND_RES);
		break;
	}
}