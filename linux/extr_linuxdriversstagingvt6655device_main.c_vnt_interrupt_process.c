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
struct TYPE_5__ {int int_works; } ;
struct ieee80211_low_level_stats {int dot11RTSSuccessCount; int dot11RTSFailureCount; int dot11ACKFailureCount; int dot11FCSErrorCount; } ;
struct vnt_private {scalar_t__ op_mode; int bBeaconSent; int bIsBeaconBufReadySet; int /*<<< orphan*/  lock; TYPE_2__ opts; scalar_t__ PortOffset; int /*<<< orphan*/  hw; TYPE_3__* vif; scalar_t__ cbBeaconBufReadySetCnt; scalar_t__ bEnablePSMode; struct ieee80211_low_level_stats low_stats; } ;
struct TYPE_4__ {int beacon_int; scalar_t__ enable_beacon; } ;
struct TYPE_6__ {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 scalar_t__ AVAIL_TD (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int ISR_AC0DMA ; 
 int ISR_BNTX ; 
 int ISR_FETALERR ; 
 int ISR_RXDMA0 ; 
 int ISR_RXDMA1 ; 
 int ISR_SOFTTIMER1 ; 
 int ISR_TBTT ; 
 int ISR_TXDMA0 ; 
 scalar_t__ MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvOneShotTimer1MicroSec (struct vnt_private*,int) ; 
 int /*<<< orphan*/  MACvReadISR (scalar_t__,int*) ; 
 int /*<<< orphan*/  MACvReadMIBCounter (scalar_t__,int*) ; 
 int /*<<< orphan*/  MACvReceive0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvReceive1 (scalar_t__) ; 
 int /*<<< orphan*/  MACvWriteISR (scalar_t__,int) ; 
 int MAKE_BEACON_RESERVED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  PSbIsNextTBTTWakeUp (void*) ; 
 int /*<<< orphan*/  SOFTPWRCTL_SWPECTI ; 
 int /*<<< orphan*/  TYPE_AC0DMA ; 
 int /*<<< orphan*/  TYPE_RXDMA0 ; 
 int /*<<< orphan*/  TYPE_RXDMA1 ; 
 int /*<<< orphan*/  TYPE_TXDMA0 ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_error (struct vnt_private*,int) ; 
 scalar_t__ device_rx_srv (struct vnt_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_tx_srv (struct vnt_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_queue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vnt_beacon_make (struct vnt_private*,TYPE_3__*) ; 
 int /*<<< orphan*/  vnt_check_bb_vga (struct vnt_private*) ; 

__attribute__((used)) static void vnt_interrupt_process(struct vnt_private *priv)
{
	struct ieee80211_low_level_stats *low_stats = &priv->low_stats;
	int             max_count = 0;
	u32 mib_counter;
	u32 isr;
	unsigned long flags;

	MACvReadISR(priv->PortOffset, &isr);

	if (isr == 0)
		return;

	if (isr == 0xffffffff) {
		pr_debug("isr = 0xffff\n");
		return;
	}

	spin_lock_irqsave(&priv->lock, flags);

	/* Read low level stats */
	MACvReadMIBCounter(priv->PortOffset, &mib_counter);

	low_stats->dot11RTSSuccessCount += mib_counter & 0xff;
	low_stats->dot11RTSFailureCount += (mib_counter >> 8) & 0xff;
	low_stats->dot11ACKFailureCount += (mib_counter >> 16) & 0xff;
	low_stats->dot11FCSErrorCount += (mib_counter >> 24) & 0xff;

	/*
	 * TBD....
	 * Must do this after doing rx/tx, cause ISR bit is slow
	 * than RD/TD write back
	 * update ISR counter
	 */
	while (isr && priv->vif) {
		MACvWriteISR(priv->PortOffset, isr);

		if (isr & ISR_FETALERR) {
			pr_debug(" ISR_FETALERR\n");
			VNSvOutPortB(priv->PortOffset + MAC_REG_SOFTPWRCTL, 0);
			VNSvOutPortW(priv->PortOffset +
				     MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPECTI);
			device_error(priv, isr);
		}

		if (isr & ISR_TBTT) {
			if (priv->op_mode != NL80211_IFTYPE_ADHOC)
				vnt_check_bb_vga(priv);

			priv->bBeaconSent = false;
			if (priv->bEnablePSMode)
				PSbIsNextTBTTWakeUp((void *)priv);

			if ((priv->op_mode == NL80211_IFTYPE_AP ||
			    priv->op_mode == NL80211_IFTYPE_ADHOC) &&
			    priv->vif->bss_conf.enable_beacon) {
				MACvOneShotTimer1MicroSec(priv,
							  (priv->vif->bss_conf.beacon_int - MAKE_BEACON_RESERVED) << 10);
			}

			/* TODO: adhoc PS mode */
		}

		if (isr & ISR_BNTX) {
			if (priv->op_mode == NL80211_IFTYPE_ADHOC) {
				priv->bIsBeaconBufReadySet = false;
				priv->cbBeaconBufReadySetCnt = 0;
			}

			priv->bBeaconSent = true;
		}

		if (isr & ISR_RXDMA0)
			max_count += device_rx_srv(priv, TYPE_RXDMA0);

		if (isr & ISR_RXDMA1)
			max_count += device_rx_srv(priv, TYPE_RXDMA1);

		if (isr & ISR_TXDMA0)
			max_count += device_tx_srv(priv, TYPE_TXDMA0);

		if (isr & ISR_AC0DMA)
			max_count += device_tx_srv(priv, TYPE_AC0DMA);

		if (isr & ISR_SOFTTIMER1) {
			if (priv->vif->bss_conf.enable_beacon)
				vnt_beacon_make(priv, priv->vif);
		}

		/* If both buffers available wake the queue */
		if (AVAIL_TD(priv, TYPE_TXDMA0) &&
		    AVAIL_TD(priv, TYPE_AC0DMA) &&
		    ieee80211_queue_stopped(priv->hw, 0))
			ieee80211_wake_queues(priv->hw);

		MACvReadISR(priv->PortOffset, &isr);

		MACvReceive0(priv->PortOffset);
		MACvReceive1(priv->PortOffset);

		if (max_count > priv->opts.int_works)
			break;
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}