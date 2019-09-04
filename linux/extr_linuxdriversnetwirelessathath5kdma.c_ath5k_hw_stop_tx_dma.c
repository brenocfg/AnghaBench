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
struct TYPE_4__ {int /*<<< orphan*/  q_tx_num; } ;
struct TYPE_5__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {scalar_t__ ah_version; int ah_mac_version; TYPE_3__* ah_txq; TYPE_2__ ah_capabilities; } ;
struct TYPE_6__ {int tqi_type; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_ASSERT_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_BSR ; 
 int /*<<< orphan*/  AR5K_CR ; 
 int AR5K_CR_TXD0 ; 
 int AR5K_CR_TXD1 ; 
 int AR5K_CR_TXE0 ; 
 int /*<<< orphan*/  AR5K_DIAG_SW_5211 ; 
 int AR5K_DIAG_SW_CHANNEL_IDLE_HIGH ; 
 int AR5K_QCU_MISC_DCU_EARLY ; 
 int AR5K_QCU_STS_FRMPENDCNT ; 
 int /*<<< orphan*/  AR5K_QCU_TXD ; 
 int /*<<< orphan*/  AR5K_QCU_TXE ; 
 int /*<<< orphan*/  AR5K_QUEUE_MISC (unsigned int) ; 
 int /*<<< orphan*/  AR5K_QUEUE_STATUS (unsigned int) ; 
 int /*<<< orphan*/  AR5K_QUIET_CTL1 ; 
 int /*<<< orphan*/  AR5K_QUIET_CTL1_NEXT_QT_TSF ; 
 int AR5K_QUIET_CTL1_QT_EN ; 
 int /*<<< orphan*/  AR5K_QUIET_CTL2 ; 
 int /*<<< orphan*/  AR5K_QUIET_CTL2_QT_DUR ; 
 int /*<<< orphan*/  AR5K_QUIET_CTL2_QT_PER ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_REG_READ_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int AR5K_REG_SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int AR5K_SREV_AR2414 ; 
 int /*<<< orphan*/  AR5K_TSF_L32_5211 ; 
#define  AR5K_TX_QUEUE_BEACON 130 
#define  AR5K_TX_QUEUE_CAB 129 
#define  AR5K_TX_QUEUE_DATA 128 
 int AR5K_TX_QUEUE_INACTIVE ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_DMA ; 
 int EBUSY ; 
 int EINVAL ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
ath5k_hw_stop_tx_dma(struct ath5k_hw *ah, unsigned int queue)
{
	unsigned int i = 40;
	u32 tx_queue, pending;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return if queue is declared inactive */
	if (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return -EINVAL;

	if (ah->ah_version == AR5K_AR5210) {
		tx_queue = ath5k_hw_reg_read(ah, AR5K_CR);

		/*
		 * Set by queue type
		 */
		switch (ah->ah_txq[queue].tqi_type) {
		case AR5K_TX_QUEUE_DATA:
			tx_queue |= AR5K_CR_TXD0 & ~AR5K_CR_TXE0;
			break;
		case AR5K_TX_QUEUE_BEACON:
		case AR5K_TX_QUEUE_CAB:
			/* XXX Fix me... */
			tx_queue |= AR5K_CR_TXD1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_write(ah, 0, AR5K_BSR);
			break;
		default:
			return -EINVAL;
		}

		/* Stop queue */
		ath5k_hw_reg_write(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_read(ah, AR5K_CR);
	} else {

		/*
		 * Enable DCU early termination to quickly
		 * flush any pending frames from QCU
		 */
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_DCU_EARLY);

		/*
		 * Schedule TX disable and wait until queue is empty
		 */
		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXD, queue);

		/* Wait for queue to stop */
		for (i = 1000; i > 0 &&
		(AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue) != 0);
		i--)
			udelay(100);

		if (AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"queue %i didn't stop !\n", queue);

		/* Check for pending frames */
		i = 1000;
		do {
			pending = ath5k_hw_reg_read(ah,
				AR5K_QUEUE_STATUS(queue)) &
				AR5K_QCU_STS_FRMPENDCNT;
			udelay(100);
		} while (--i && pending);

		/* For 2413+ order PCU to drop packets using
		 * QUIET mechanism */
		if (ah->ah_mac_version >= (AR5K_SREV_AR2414 >> 4) &&
		    pending) {
			/* Set periodicity and duration */
			ath5k_hw_reg_write(ah,
				AR5K_REG_SM(100, AR5K_QUIET_CTL2_QT_PER)|
				AR5K_REG_SM(10, AR5K_QUIET_CTL2_QT_DUR),
				AR5K_QUIET_CTL2);

			/* Enable quiet period for current TSF */
			ath5k_hw_reg_write(ah,
				AR5K_QUIET_CTL1_QT_EN |
				AR5K_REG_SM(ath5k_hw_reg_read(ah,
						AR5K_TSF_L32_5211) >> 10,
						AR5K_QUIET_CTL1_NEXT_QT_TSF),
				AR5K_QUIET_CTL1);

			/* Force channel idle high */
			AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW_5211,
					AR5K_DIAG_SW_CHANNEL_IDLE_HIGH);

			/* Wait a while and disable mechanism */
			udelay(400);
			AR5K_REG_DISABLE_BITS(ah, AR5K_QUIET_CTL1,
						AR5K_QUIET_CTL1_QT_EN);

			/* Re-check for pending frames */
			i = 100;
			do {
				pending = ath5k_hw_reg_read(ah,
					AR5K_QUEUE_STATUS(queue)) &
					AR5K_QCU_STS_FRMPENDCNT;
				udelay(100);
			} while (--i && pending);

			AR5K_REG_DISABLE_BITS(ah, AR5K_DIAG_SW_5211,
					AR5K_DIAG_SW_CHANNEL_IDLE_HIGH);

			if (pending)
				ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"quiet mechanism didn't work q:%i !\n",
					queue);
		}

		/*
		 * Disable DCU early termination
		 */
		AR5K_REG_DISABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_DCU_EARLY);

		/* Clear register */
		ath5k_hw_reg_write(ah, 0, AR5K_QCU_TXD);
		if (pending) {
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"tx dma didn't stop (q:%i, frm:%i) !\n",
					queue, pending);
			return -EBUSY;
		}
	}

	/* TODO: Check for success on 5210 else return error */
	return 0;
}