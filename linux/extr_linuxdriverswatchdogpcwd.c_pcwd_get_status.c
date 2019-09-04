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
struct TYPE_2__ {scalar_t__ revision; int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ PCWD_REVISION_A ; 
 int WDIOF_CARDRESET ; 
 int WDIOF_OVERHEAT ; 
 int WD_REVC_TTRP ; 
 int WD_REVC_WTRP ; 
 int WD_T110 ; 
 int WD_WDRST ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ temp_panic ; 

__attribute__((used)) static int pcwd_get_status(int *status)
{
	int control_status;

	*status = 0;
	spin_lock(&pcwd_private.io_lock);
	if (pcwd_private.revision == PCWD_REVISION_A)
		/* Rev A cards return status information from
		 * the base register, which is used for the
		 * temperature in other cards. */
		control_status = inb(pcwd_private.io_addr);
	else {
		/* Rev C cards return card status in the base
		 * address + 1 register. And use different bits
		 * to indicate a card initiated reset, and an
		 * over-temperature condition. And the reboot
		 * status can be reset. */
		control_status = inb(pcwd_private.io_addr + 1);
	}
	spin_unlock(&pcwd_private.io_lock);

	if (pcwd_private.revision == PCWD_REVISION_A) {
		if (control_status & WD_WDRST)
			*status |= WDIOF_CARDRESET;

		if (control_status & WD_T110) {
			*status |= WDIOF_OVERHEAT;
			if (temp_panic) {
				pr_info("Temperature overheat trip!\n");
				kernel_power_off();
			}
		}
	} else {
		if (control_status & WD_REVC_WTRP)
			*status |= WDIOF_CARDRESET;

		if (control_status & WD_REVC_TTRP) {
			*status |= WDIOF_OVERHEAT;
			if (temp_panic) {
				pr_info("Temperature overheat trip!\n");
				kernel_power_off();
			}
		}
	}

	return 0;
}