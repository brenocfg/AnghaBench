#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u32 ;
struct brcmf_sdio_dev {scalar_t__ state; int /*<<< orphan*/  func1; } ;
struct TYPE_4__ {int f1regdata; } ;
struct brcmf_sdio {scalar_t__ clkstate; unsigned long hostintmask; int ctrl_frame_stat; int ctrl_frame_err; int dpc_triggered; int /*<<< orphan*/  flowcontrol; int /*<<< orphan*/  txq; int /*<<< orphan*/  fcstate; int /*<<< orphan*/  ipend; int /*<<< orphan*/  intstatus; struct brcmf_sdio_dev* sdiodev; int /*<<< orphan*/  txminmax; scalar_t__ rxpending; int /*<<< orphan*/  ctrl_frame_len; int /*<<< orphan*/  ctrl_frame_buf; int /*<<< orphan*/  rxbound; scalar_t__ rxskip; TYPE_2__ sdcnt; int /*<<< orphan*/  sr_enabled; scalar_t__ txbound; TYPE_1__* sdio_core; } ;
struct TYPE_3__ {unsigned long base; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_DATA ; 
 scalar_t__ CLK_AVAIL ; 
 scalar_t__ CLK_PENDING ; 
 int ENODEV ; 
 unsigned long I_CHIPACTIVE ; 
 unsigned long I_HMB_FC_CHANGE ; 
 unsigned long I_HMB_FC_STATE ; 
 unsigned long I_HMB_FRAME_IND ; 
 unsigned long I_HMB_HOST_INT ; 
 unsigned long I_RD_OOSYNC ; 
 unsigned long I_SBINT ; 
 unsigned long I_WR_OOSYNC ; 
 int /*<<< orphan*/  SBSDIO_DEVCTL_CA_INT_ONLY ; 
 int /*<<< orphan*/  SBSDIO_DEVICE_CTL ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 scalar_t__ SBSDIO_HTAV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDIO ; 
 unsigned long SD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_or (unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned long atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_sdio_bus_sleep (struct brcmf_sdio*,int,int) ; 
 int /*<<< orphan*/  brcmf_sdio_clrintr (struct brcmf_sdio*) ; 
 unsigned long brcmf_sdio_hostmail (struct brcmf_sdio*) ; 
 int brcmf_sdio_intr_rstatus (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_readframes (struct brcmf_sdio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_sendfromq (struct brcmf_sdio*,scalar_t__) ; 
 int brcmf_sdio_tx_ctrlframe (struct brcmf_sdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_wait_event_wakeup (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdiod_readb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int*) ; 
 unsigned long brcmf_sdiod_readl (struct brcmf_sdio_dev*,unsigned long,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (struct brcmf_sdio_dev*,unsigned long,unsigned long,int*) ; 
 scalar_t__ brcmu_pktq_mlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ data_ok (struct brcmf_sdio*) ; 
 unsigned long intstatus ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void brcmf_sdio_dpc(struct brcmf_sdio *bus)
{
	struct brcmf_sdio_dev *sdiod = bus->sdiodev;
	u32 newstatus = 0;
	u32 intstat_addr = bus->sdio_core->base + SD_REG(intstatus);
	unsigned long intstatus;
	uint txlimit = bus->txbound;	/* Tx frames to send before resched */
	uint framecnt;			/* Temporary counter of tx/rx frames */
	int err = 0;

	brcmf_dbg(SDIO, "Enter\n");

	sdio_claim_host(bus->sdiodev->func1);

	/* If waiting for HTAVAIL, check status */
	if (!bus->sr_enabled && bus->clkstate == CLK_PENDING) {
		u8 clkctl, devctl = 0;

#ifdef DEBUG
		/* Check for inconsistent device control */
		devctl = brcmf_sdiod_readb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   &err);
#endif				/* DEBUG */

		/* Read CSR, if clock on switch to AVAIL, else ignore */
		clkctl = brcmf_sdiod_readb(bus->sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR, &err);

		brcmf_dbg(SDIO, "DPC: PENDING, devctl 0x%02x clkctl 0x%02x\n",
			  devctl, clkctl);

		if (SBSDIO_HTAV(clkctl)) {
			devctl = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_writeb(bus->sdiodev,
					   SBSDIO_DEVICE_CTL, devctl, &err);
			bus->clkstate = CLK_AVAIL;
		}
	}

	/* Make sure backplane clock is on */
	brcmf_sdio_bus_sleep(bus, false, true);

	/* Pending interrupt indicates new device status */
	if (atomic_read(&bus->ipend) > 0) {
		atomic_set(&bus->ipend, 0);
		err = brcmf_sdio_intr_rstatus(bus);
	}

	/* Start with leftover status bits */
	intstatus = atomic_xchg(&bus->intstatus, 0);

	/* Handle flow-control change: read new state in case our ack
	 * crossed another change interrupt.  If change still set, assume
	 * FC ON for safety, let next loop through do the debounce.
	 */
	if (intstatus & I_HMB_FC_CHANGE) {
		intstatus &= ~I_HMB_FC_CHANGE;
		brcmf_sdiod_writel(sdiod, intstat_addr, I_HMB_FC_CHANGE, &err);

		newstatus = brcmf_sdiod_readl(sdiod, intstat_addr, &err);

		bus->sdcnt.f1regdata += 2;
		atomic_set(&bus->fcstate,
			   !!(newstatus & (I_HMB_FC_STATE | I_HMB_FC_CHANGE)));
		intstatus |= (newstatus & bus->hostintmask);
	}

	/* Handle host mailbox indication */
	if (intstatus & I_HMB_HOST_INT) {
		intstatus &= ~I_HMB_HOST_INT;
		intstatus |= brcmf_sdio_hostmail(bus);
	}

	sdio_release_host(bus->sdiodev->func1);

	/* Generally don't ask for these, can get CRC errors... */
	if (intstatus & I_WR_OOSYNC) {
		brcmf_err("Dongle reports WR_OOSYNC\n");
		intstatus &= ~I_WR_OOSYNC;
	}

	if (intstatus & I_RD_OOSYNC) {
		brcmf_err("Dongle reports RD_OOSYNC\n");
		intstatus &= ~I_RD_OOSYNC;
	}

	if (intstatus & I_SBINT) {
		brcmf_err("Dongle reports SBINT\n");
		intstatus &= ~I_SBINT;
	}

	/* Would be active due to wake-wlan in gSPI */
	if (intstatus & I_CHIPACTIVE) {
		brcmf_dbg(SDIO, "Dongle reports CHIPACTIVE\n");
		intstatus &= ~I_CHIPACTIVE;
	}

	/* Ignore frame indications if rxskip is set */
	if (bus->rxskip)
		intstatus &= ~I_HMB_FRAME_IND;

	/* On frame indication, read available frames */
	if ((intstatus & I_HMB_FRAME_IND) && (bus->clkstate == CLK_AVAIL)) {
		brcmf_sdio_readframes(bus, bus->rxbound);
		if (!bus->rxpending)
			intstatus &= ~I_HMB_FRAME_IND;
	}

	/* Keep still-pending events for next scheduling */
	if (intstatus)
		atomic_or(intstatus, &bus->intstatus);

	brcmf_sdio_clrintr(bus);

	if (bus->ctrl_frame_stat && (bus->clkstate == CLK_AVAIL) &&
	    data_ok(bus)) {
		sdio_claim_host(bus->sdiodev->func1);
		if (bus->ctrl_frame_stat) {
			err = brcmf_sdio_tx_ctrlframe(bus,  bus->ctrl_frame_buf,
						      bus->ctrl_frame_len);
			bus->ctrl_frame_err = err;
			wmb();
			bus->ctrl_frame_stat = false;
		}
		sdio_release_host(bus->sdiodev->func1);
		brcmf_sdio_wait_event_wakeup(bus);
	}
	/* Send queued frames (limit 1 if rx may still be pending) */
	if ((bus->clkstate == CLK_AVAIL) && !atomic_read(&bus->fcstate) &&
	    brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol) && txlimit &&
	    data_ok(bus)) {
		framecnt = bus->rxpending ? min(txlimit, bus->txminmax) :
					    txlimit;
		brcmf_sdio_sendfromq(bus, framecnt);
	}

	if ((bus->sdiodev->state != BRCMF_SDIOD_DATA) || (err != 0)) {
		brcmf_err("failed backplane access over SDIO, halting operation\n");
		atomic_set(&bus->intstatus, 0);
		if (bus->ctrl_frame_stat) {
			sdio_claim_host(bus->sdiodev->func1);
			if (bus->ctrl_frame_stat) {
				bus->ctrl_frame_err = -ENODEV;
				wmb();
				bus->ctrl_frame_stat = false;
				brcmf_sdio_wait_event_wakeup(bus);
			}
			sdio_release_host(bus->sdiodev->func1);
		}
	} else if (atomic_read(&bus->intstatus) ||
		   atomic_read(&bus->ipend) > 0 ||
		   (!atomic_read(&bus->fcstate) &&
		    brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol) &&
		    data_ok(bus))) {
		bus->dpc_triggered = true;
	}
}