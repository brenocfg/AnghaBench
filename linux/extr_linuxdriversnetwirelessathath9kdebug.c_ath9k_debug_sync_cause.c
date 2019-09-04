#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  mac_sleep_access; int /*<<< orphan*/  mac_asleep; int /*<<< orphan*/  mac_awake; int /*<<< orphan*/  pm_access; int /*<<< orphan*/  local_timeout; int /*<<< orphan*/  radm_cpl_timeout; int /*<<< orphan*/  radm_cpl_ecrc_err; int /*<<< orphan*/  radm_cpl_tlp_abort; int /*<<< orphan*/  radm_cpl_dllp_abort; int /*<<< orphan*/  radm_cpl_ep; int /*<<< orphan*/  trcv_fifo_perr; int /*<<< orphan*/  host1_perr; int /*<<< orphan*/  host1_fatal; int /*<<< orphan*/  pci_mode_conflict; int /*<<< orphan*/  apb_timeout; int /*<<< orphan*/  eeprom_illegal_access; int /*<<< orphan*/  sync_mac_irq; int /*<<< orphan*/  sync_rtc_irq; int /*<<< orphan*/  sync_cause_all; } ;
struct TYPE_5__ {TYPE_1__ istats; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct ath_softc {TYPE_3__ debug; } ;

/* Variables and functions */
 int AR_INTR_SYNC_APB_TIMEOUT ; 
 int AR_INTR_SYNC_EEPROM_ILLEGAL_ACCESS ; 
 int AR_INTR_SYNC_HOST1_FATAL ; 
 int AR_INTR_SYNC_HOST1_PERR ; 
 int AR_INTR_SYNC_LOCAL_TIMEOUT ; 
 int AR_INTR_SYNC_MAC_ASLEEP ; 
 int AR_INTR_SYNC_MAC_AWAKE ; 
 int AR_INTR_SYNC_MAC_IRQ ; 
 int AR_INTR_SYNC_MAC_SLEEP_ACCESS ; 
 int AR_INTR_SYNC_PCI_MODE_CONFLICT ; 
 int AR_INTR_SYNC_PM_ACCESS ; 
 int AR_INTR_SYNC_RADM_CPL_DLLP_ABORT ; 
 int AR_INTR_SYNC_RADM_CPL_ECRC_ERR ; 
 int AR_INTR_SYNC_RADM_CPL_EP ; 
 int AR_INTR_SYNC_RADM_CPL_TIMEOUT ; 
 int AR_INTR_SYNC_RADM_CPL_TLP_ABORT ; 
 int AR_INTR_SYNC_RTC_IRQ ; 
 int AR_INTR_SYNC_TRCV_FIFO_PERR ; 

void ath9k_debug_sync_cause(struct ath_softc *sc, u32 sync_cause)
{
	if (sync_cause)
		sc->debug.stats.istats.sync_cause_all++;
	if (sync_cause & AR_INTR_SYNC_RTC_IRQ)
		sc->debug.stats.istats.sync_rtc_irq++;
	if (sync_cause & AR_INTR_SYNC_MAC_IRQ)
		sc->debug.stats.istats.sync_mac_irq++;
	if (sync_cause & AR_INTR_SYNC_EEPROM_ILLEGAL_ACCESS)
		sc->debug.stats.istats.eeprom_illegal_access++;
	if (sync_cause & AR_INTR_SYNC_APB_TIMEOUT)
		sc->debug.stats.istats.apb_timeout++;
	if (sync_cause & AR_INTR_SYNC_PCI_MODE_CONFLICT)
		sc->debug.stats.istats.pci_mode_conflict++;
	if (sync_cause & AR_INTR_SYNC_HOST1_FATAL)
		sc->debug.stats.istats.host1_fatal++;
	if (sync_cause & AR_INTR_SYNC_HOST1_PERR)
		sc->debug.stats.istats.host1_perr++;
	if (sync_cause & AR_INTR_SYNC_TRCV_FIFO_PERR)
		sc->debug.stats.istats.trcv_fifo_perr++;
	if (sync_cause & AR_INTR_SYNC_RADM_CPL_EP)
		sc->debug.stats.istats.radm_cpl_ep++;
	if (sync_cause & AR_INTR_SYNC_RADM_CPL_DLLP_ABORT)
		sc->debug.stats.istats.radm_cpl_dllp_abort++;
	if (sync_cause & AR_INTR_SYNC_RADM_CPL_TLP_ABORT)
		sc->debug.stats.istats.radm_cpl_tlp_abort++;
	if (sync_cause & AR_INTR_SYNC_RADM_CPL_ECRC_ERR)
		sc->debug.stats.istats.radm_cpl_ecrc_err++;
	if (sync_cause & AR_INTR_SYNC_RADM_CPL_TIMEOUT)
		sc->debug.stats.istats.radm_cpl_timeout++;
	if (sync_cause & AR_INTR_SYNC_LOCAL_TIMEOUT)
		sc->debug.stats.istats.local_timeout++;
	if (sync_cause & AR_INTR_SYNC_PM_ACCESS)
		sc->debug.stats.istats.pm_access++;
	if (sync_cause & AR_INTR_SYNC_MAC_AWAKE)
		sc->debug.stats.istats.mac_awake++;
	if (sync_cause & AR_INTR_SYNC_MAC_ASLEEP)
		sc->debug.stats.istats.mac_asleep++;
	if (sync_cause & AR_INTR_SYNC_MAC_SLEEP_ACCESS)
		sc->debug.stats.istats.mac_sleep_access++;
}