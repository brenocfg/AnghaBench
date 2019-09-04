#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  private; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  mac_sleep_access; int /*<<< orphan*/  mac_asleep; int /*<<< orphan*/  mac_awake; int /*<<< orphan*/  pm_access; int /*<<< orphan*/  local_timeout; int /*<<< orphan*/  radm_cpl_timeout; int /*<<< orphan*/  radm_cpl_ecrc_err; int /*<<< orphan*/  radm_cpl_tlp_abort; int /*<<< orphan*/  radm_cpl_dllp_abort; int /*<<< orphan*/  radm_cpl_ep; int /*<<< orphan*/  trcv_fifo_perr; int /*<<< orphan*/  host1_perr; int /*<<< orphan*/  host1_fatal; int /*<<< orphan*/  pci_mode_conflict; int /*<<< orphan*/  apb_timeout; int /*<<< orphan*/  eeprom_illegal_access; int /*<<< orphan*/  sync_mac_irq; int /*<<< orphan*/  sync_rtc_irq; int /*<<< orphan*/  sync_cause_all; int /*<<< orphan*/  total; int /*<<< orphan*/  gen_timer; int /*<<< orphan*/  mci; int /*<<< orphan*/  tsfoor; int /*<<< orphan*/  dtim; int /*<<< orphan*/  dtimsync; int /*<<< orphan*/  cabend; int /*<<< orphan*/  tim; int /*<<< orphan*/  gtt; int /*<<< orphan*/  cst; int /*<<< orphan*/  bnr; int /*<<< orphan*/  bmiss; int /*<<< orphan*/  swba; int /*<<< orphan*/  rx_keycache_miss; int /*<<< orphan*/  rxphyerr; int /*<<< orphan*/  mib; int /*<<< orphan*/  txurn; int /*<<< orphan*/  txok; int /*<<< orphan*/  rxorn; int /*<<< orphan*/  rxeol; int /*<<< orphan*/  rxok; int /*<<< orphan*/  bb_watchdog; int /*<<< orphan*/  rxhp; int /*<<< orphan*/  rxlp; } ;
struct TYPE_9__ {TYPE_5__ istats; } ;
struct TYPE_8__ {TYPE_4__ stats; } ;
struct ath_softc {TYPE_3__ debug; TYPE_2__* sc_ah; } ;
struct TYPE_6__ {int hw_caps; } ;
struct TYPE_7__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_EDMA ; 
 struct ieee80211_hw* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int read_file_interrupt(struct seq_file *file, void *data)
{
	struct ieee80211_hw *hw = dev_get_drvdata(file->private);
	struct ath_softc *sc = hw->priv;

#define PR_IS(a, s)						\
	do {							\
		seq_printf(file, "%21s: %10u\n", a,		\
			   sc->debug.stats.istats.s);		\
	} while (0)

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		PR_IS("RXLP", rxlp);
		PR_IS("RXHP", rxhp);
		PR_IS("WATCHDOG", bb_watchdog);
	} else {
		PR_IS("RX", rxok);
	}
	PR_IS("RXEOL", rxeol);
	PR_IS("RXORN", rxorn);
	PR_IS("TX", txok);
	PR_IS("TXURN", txurn);
	PR_IS("MIB", mib);
	PR_IS("RXPHY", rxphyerr);
	PR_IS("RXKCM", rx_keycache_miss);
	PR_IS("SWBA", swba);
	PR_IS("BMISS", bmiss);
	PR_IS("BNR", bnr);
	PR_IS("CST", cst);
	PR_IS("GTT", gtt);
	PR_IS("TIM", tim);
	PR_IS("CABEND", cabend);
	PR_IS("DTIMSYNC", dtimsync);
	PR_IS("DTIM", dtim);
	PR_IS("TSFOOR", tsfoor);
	PR_IS("MCI", mci);
	PR_IS("GENTIMER", gen_timer);
	PR_IS("TOTAL", total);

	seq_puts(file, "SYNC_CAUSE stats:\n");

	PR_IS("Sync-All", sync_cause_all);
	PR_IS("RTC-IRQ", sync_rtc_irq);
	PR_IS("MAC-IRQ", sync_mac_irq);
	PR_IS("EEPROM-Illegal-Access", eeprom_illegal_access);
	PR_IS("APB-Timeout", apb_timeout);
	PR_IS("PCI-Mode-Conflict", pci_mode_conflict);
	PR_IS("HOST1-Fatal", host1_fatal);
	PR_IS("HOST1-Perr", host1_perr);
	PR_IS("TRCV-FIFO-Perr", trcv_fifo_perr);
	PR_IS("RADM-CPL-EP", radm_cpl_ep);
	PR_IS("RADM-CPL-DLLP-Abort", radm_cpl_dllp_abort);
	PR_IS("RADM-CPL-TLP-Abort", radm_cpl_tlp_abort);
	PR_IS("RADM-CPL-ECRC-Err", radm_cpl_ecrc_err);
	PR_IS("RADM-CPL-Timeout", radm_cpl_timeout);
	PR_IS("Local-Bus-Timeout", local_timeout);
	PR_IS("PM-Access", pm_access);
	PR_IS("MAC-Awake", mac_awake);
	PR_IS("MAC-Asleep", mac_asleep);
	PR_IS("MAC-Sleep-Access", mac_sleep_access);

	return 0;
}