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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct iTCO_wdt_private {int iTCO_version; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  no_reboot_priv; scalar_t__ (* update_no_reboot_bit ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  smi_res; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TCO1_CNT (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  TCO_RLD (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  iTCO_vendor_pre_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 struct iTCO_wdt_private* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int iTCO_wdt_start(struct watchdog_device *wd_dev)
{
	struct iTCO_wdt_private *p = watchdog_get_drvdata(wd_dev);
	unsigned int val;

	spin_lock(&p->io_lock);

	iTCO_vendor_pre_start(p->smi_res, wd_dev->timeout);

	/* disable chipset's NO_REBOOT bit */
	if (p->update_no_reboot_bit(p->no_reboot_priv, false)) {
		spin_unlock(&p->io_lock);
		pr_err("failed to reset NO_REBOOT flag, reboot disabled by hardware/BIOS\n");
		return -EIO;
	}

	/* Force the timer to its reload value by writing to the TCO_RLD
	   register */
	if (p->iTCO_version >= 2)
		outw(0x01, TCO_RLD(p));
	else if (p->iTCO_version == 1)
		outb(0x01, TCO_RLD(p));

	/* Bit 11: TCO Timer Halt -> 0 = The TCO timer is enabled to count */
	val = inw(TCO1_CNT(p));
	val &= 0xf7ff;
	outw(val, TCO1_CNT(p));
	val = inw(TCO1_CNT(p));
	spin_unlock(&p->io_lock);

	if (val & 0x0800)
		return -1;
	return 0;
}