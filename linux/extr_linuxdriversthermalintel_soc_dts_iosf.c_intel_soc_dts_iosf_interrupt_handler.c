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
typedef  int u32 ;
struct intel_soc_dts_sensors {int /*<<< orphan*/  intr_notify_lock; TYPE_1__* soc_dts; } ;
struct TYPE_2__ {int /*<<< orphan*/  tzone; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  SOC_DTS_OFFSET_PTMC ; 
 int /*<<< orphan*/  SOC_DTS_OFFSET_PTTSS ; 
 int SOC_DTS_PTMC_APIC_DEASSERT_BIT ; 
 int SOC_DTS_TRIP_MASK ; 
 int SOC_MAX_DTS_SENSORS ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_soc_dts_iosf_interrupt_handler(struct intel_soc_dts_sensors *sensors)
{
	u32 sticky_out;
	int status;
	u32 ptmc_out;
	unsigned long flags;

	spin_lock_irqsave(&sensors->intr_notify_lock, flags);

	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTMC, &ptmc_out);
	ptmc_out |= SOC_DTS_PTMC_APIC_DEASSERT_BIT;
	status = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTMC, ptmc_out);

	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTTSS, &sticky_out);
	pr_debug("status %d PTTSS %x\n", status, sticky_out);
	if (sticky_out & SOC_DTS_TRIP_MASK) {
		int i;
		/* reset sticky bit */
		status = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
					SOC_DTS_OFFSET_PTTSS, sticky_out);
		spin_unlock_irqrestore(&sensors->intr_notify_lock, flags);

		for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) {
			pr_debug("TZD update for zone %d\n", i);
			thermal_zone_device_update(sensors->soc_dts[i].tzone,
						   THERMAL_EVENT_UNSPECIFIED);
		}
	} else
		spin_unlock_irqrestore(&sensors->intr_notify_lock, flags);
}