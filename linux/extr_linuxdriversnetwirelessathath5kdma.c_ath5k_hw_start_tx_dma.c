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
struct TYPE_6__ {int /*<<< orphan*/  q_tx_num; } ;
struct TYPE_5__ {TYPE_3__ cap_queues; } ;
struct ath5k_hw {scalar_t__ ah_version; TYPE_1__* ah_txq; TYPE_2__ ah_capabilities; } ;
struct TYPE_4__ {int tqi_type; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_ASSERT_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int AR5K_BCR_BDMAE ; 
 int AR5K_BCR_TQ1FV ; 
 int AR5K_BCR_TQ1V ; 
 int /*<<< orphan*/  AR5K_BSR ; 
 int /*<<< orphan*/  AR5K_CR ; 
 int AR5K_CR_TXD0 ; 
 int AR5K_CR_TXD1 ; 
 int AR5K_CR_TXE0 ; 
 int AR5K_CR_TXE1 ; 
 int /*<<< orphan*/  AR5K_QCU_TXD ; 
 int /*<<< orphan*/  AR5K_QCU_TXE ; 
 scalar_t__ AR5K_REG_READ_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
#define  AR5K_TX_QUEUE_BEACON 130 
#define  AR5K_TX_QUEUE_CAB 129 
#define  AR5K_TX_QUEUE_DATA 128 
 int AR5K_TX_QUEUE_INACTIVE ; 
 int EINVAL ; 
 int EIO ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

int
ath5k_hw_start_tx_dma(struct ath5k_hw *ah, unsigned int queue)
{
	u32 tx_queue;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return if queue is declared inactive */
	if (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return -EINVAL;

	if (ah->ah_version == AR5K_AR5210) {
		tx_queue = ath5k_hw_reg_read(ah, AR5K_CR);

		/*
		 * Set the queue by type on 5210
		 */
		switch (ah->ah_txq[queue].tqi_type) {
		case AR5K_TX_QUEUE_DATA:
			tx_queue |= AR5K_CR_TXE0 & ~AR5K_CR_TXD0;
			break;
		case AR5K_TX_QUEUE_BEACON:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_write(ah, AR5K_BCR_TQ1V | AR5K_BCR_BDMAE,
					AR5K_BSR);
			break;
		case AR5K_TX_QUEUE_CAB:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_write(ah, AR5K_BCR_TQ1FV | AR5K_BCR_TQ1V |
				AR5K_BCR_BDMAE, AR5K_BSR);
			break;
		default:
			return -EINVAL;
		}
		/* Start queue */
		ath5k_hw_reg_write(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_read(ah, AR5K_CR);
	} else {
		/* Return if queue is disabled */
		if (AR5K_REG_READ_Q(ah, AR5K_QCU_TXD, queue))
			return -EIO;

		/* Start queue */
		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXE, queue);
	}

	return 0;
}