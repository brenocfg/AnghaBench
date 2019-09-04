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
struct ef4_tx_queue {int /*<<< orphan*/  queue; int /*<<< orphan*/  flush_outstanding; struct ef4_nic* efx; } ;
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AZ_TX_FLUSH_DESCQ ; 
 int /*<<< orphan*/  FRF_AZ_TX_FLUSH_DESCQ_CMD ; 
 int /*<<< orphan*/  FR_AZ_TX_FLUSH_DESCQ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ef4_farch_flush_tx_queue(struct ef4_tx_queue *tx_queue)
{
	struct ef4_nic *efx = tx_queue->efx;
	ef4_oword_t tx_flush_descq;

	WARN_ON(atomic_read(&tx_queue->flush_outstanding));
	atomic_set(&tx_queue->flush_outstanding, 1);

	EF4_POPULATE_OWORD_2(tx_flush_descq,
			     FRF_AZ_TX_FLUSH_DESCQ_CMD, 1,
			     FRF_AZ_TX_FLUSH_DESCQ, tx_queue->queue);
	ef4_writeo(efx, &tx_flush_descq, FR_AZ_TX_FLUSH_DESCQ);
}