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
struct ath9k_hw_mci {scalar_t__ bt_state; int /*<<< orphan*/  update_2g5g; scalar_t__ is_2g; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_BT_PRI ; 
 int /*<<< orphan*/  AR_MCI_BT_PRI0 ; 
 int /*<<< orphan*/  AR_MCI_BT_PRI1 ; 
 int /*<<< orphan*/  AR_MCI_BT_PRI2 ; 
 int /*<<< orphan*/  AR_MCI_BT_PRI3 ; 
 int AR_MCI_INTERRUPT_BT_PRI ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_EN ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RAW ; 
 int AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE ; 
 int AR_MCI_INTERRUPT_RX_MSG_CONT_RST ; 
 int AR_MCI_INTERRUPT_RX_MSG_LNA_INFO ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_RAW ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING ; 
 int /*<<< orphan*/  MCI ; 
 scalar_t__ MCI_ANT_ARCH_PA_LNA_SHARED (struct ath9k_hw_mci*) ; 
 scalar_t__ MCI_BT_AWAKE ; 
 scalar_t__ MCI_BT_SLEEP ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_mci_remote_reset (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_lna_transfer (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_req_wake (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_sys_waking (struct ath_hw*,int) ; 
 scalar_t__ ar9003_mci_wait_for_interrupt (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9003_mci_prep_interface(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 saved_mci_int_en;
	u32 mci_timeout = 150;

	mci->bt_state = MCI_BT_SLEEP;
	saved_mci_int_en = REG_READ(ah, AR_MCI_INTERRUPT_EN);

	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, 0);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
		  REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW));
	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
		  REG_READ(ah, AR_MCI_INTERRUPT_RAW));

	ar9003_mci_remote_reset(ah, true);
	ar9003_mci_send_req_wake(ah, true);

	if (!ar9003_mci_wait_for_interrupt(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
				  AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING, 500))
		goto clear_redunt;

	mci->bt_state = MCI_BT_AWAKE;

	/*
	 * we don't need to send more remote_reset at this moment.
	 * If BT receive first remote_reset, then BT HW will
	 * be cleaned up and will be able to receive req_wake
	 * and BT HW will respond sys_waking.
	 * In this case, WLAN will receive BT's HW sys_waking.
	 * Otherwise, if BT SW missed initial remote_reset,
	 * that remote_reset will still clean up BT MCI RX,
	 * and the req_wake will wake BT up,
	 * and BT SW will respond this req_wake with a remote_reset and
	 * sys_waking. In this case, WLAN will receive BT's SW
	 * sys_waking. In either case, BT's RX is cleaned up. So we
	 * don't need to reply BT's remote_reset now, if any.
	 * Similarly, if in any case, WLAN can receive BT's sys_waking,
	 * that means WLAN's RX is also fine.
	 */
	ar9003_mci_send_sys_waking(ah, true);
	udelay(10);

	/*
	 * Set BT priority interrupt value to be 0xff to
	 * avoid having too many BT PRIORITY interrupts.
	 */
	REG_WRITE(ah, AR_MCI_BT_PRI0, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI1, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI2, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI3, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI, 0X000000FF);

	/*
	 * A contention reset will be received after send out
	 * sys_waking. Also BT priority interrupt bits will be set.
	 * Clear those bits before the next step.
	 */

	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
		  AR_MCI_INTERRUPT_RX_MSG_CONT_RST);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW, AR_MCI_INTERRUPT_BT_PRI);

	if (mci->is_2g && MCI_ANT_ARCH_PA_LNA_SHARED(mci)) {
		ar9003_mci_send_lna_transfer(ah, true);
		udelay(5);
	}

	if (mci->is_2g && !mci->update_2g5g && MCI_ANT_ARCH_PA_LNA_SHARED(mci)) {
		if (ar9003_mci_wait_for_interrupt(ah,
					AR_MCI_INTERRUPT_RX_MSG_RAW,
					AR_MCI_INTERRUPT_RX_MSG_LNA_INFO,
					mci_timeout))
			ath_dbg(common, MCI,
				"MCI WLAN has control over the LNA & BT obeys it\n");
		else
			ath_dbg(common, MCI,
				"MCI BT didn't respond to LNA_TRANS\n");
	}

clear_redunt:
	/* Clear the extra redundant SYS_WAKING from BT */
	if ((mci->bt_state == MCI_BT_AWAKE) &&
	    (REG_READ_FIELD(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			    AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING)) &&
	    (REG_READ_FIELD(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			    AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING) == 0)) {
		REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			  AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING);
		REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
			  AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE);
	}

	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, saved_mci_int_en);
}