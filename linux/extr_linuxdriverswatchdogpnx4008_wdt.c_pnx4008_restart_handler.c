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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int EXT_MATCH0 ; 
 int M_RES1 ; 
 int M_RES2 ; 
 int NOTIFY_DONE ; 
 unsigned long REBOOT_HARD ; 
 unsigned long REBOOT_SOFT ; 
 int RESFRC1 ; 
 int RESFRC2 ; 
 int /*<<< orphan*/  WDTIM_EMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_MCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_PULSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  wdt_base ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnx4008_restart_handler(struct watchdog_device *wdd,
				   unsigned long mode, void *cmd)
{
	const char *boot_cmd = cmd;

	/*
	 * Verify if a "cmd" passed from the userspace program rebooting
	 * the system; if available, handle it.
	 * - For details, see the 'reboot' syscall in kernel/reboot.c
	 * - If the received "cmd" is not supported, use the default mode.
	 */
	if (boot_cmd) {
		if (boot_cmd[0] == 'h')
			mode = REBOOT_HARD;
		else if (boot_cmd[0] == 's')
			mode = REBOOT_SOFT;
	}

	if (mode == REBOOT_SOFT) {
		/* Force match output active */
		writel(EXT_MATCH0, WDTIM_EMR(wdt_base));
		/* Internal reset on match output (RESOUT_N not asserted) */
		writel(M_RES1, WDTIM_MCTRL(wdt_base));
	} else {
		/* Instant assert of RESETOUT_N with pulse length 1mS */
		writel(13000, WDTIM_PULSE(wdt_base));
		writel(M_RES2 | RESFRC1 | RESFRC2, WDTIM_MCTRL(wdt_base));
	}

	/* Wait for watchdog to reset system */
	mdelay(1000);

	return NOTIFY_DONE;
}