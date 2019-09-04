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
struct esas2r_adapter {int intr_mode; int /*<<< orphan*/  flags2; int /*<<< orphan*/  index; int /*<<< orphan*/  pcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_MSI_ENABLED ; 
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
#define  INTR_MODE_LEGACY 129 
#define  INTR_MODE_MSI 128 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  interrupt_mode ; 
 int pci_enable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_setup_interrupts(struct esas2r_adapter *a, int intr_mode)
{
	int i;

	/* Set up interrupt mode based on the requested value */
	switch (intr_mode) {
	case INTR_MODE_LEGACY:
use_legacy_interrupts:
		a->intr_mode = INTR_MODE_LEGACY;
		break;

	case INTR_MODE_MSI:
		i = pci_enable_msi(a->pcid);
		if (i != 0) {
			esas2r_log(ESAS2R_LOG_WARN,
				   "failed to enable MSI for adapter %d, "
				   "falling back to legacy interrupts "
				   "(err=%d)", a->index,
				   i);
			goto use_legacy_interrupts;
		}
		a->intr_mode = INTR_MODE_MSI;
		set_bit(AF2_MSI_ENABLED, &a->flags2);
		break;


	default:
		esas2r_log(ESAS2R_LOG_WARN,
			   "unknown interrupt_mode %d requested, "
			   "falling back to legacy interrupt",
			   interrupt_mode);
		goto use_legacy_interrupts;
	}
}