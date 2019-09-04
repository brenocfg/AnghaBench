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
struct ef4_tx_queue {int /*<<< orphan*/  channel; int /*<<< orphan*/  flush_outstanding; } ;
struct ef4_nic {int n_tx_channels; } ;
typedef  int /*<<< orphan*/  ef4_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_CHANNEL_MAGIC_TX_DRAIN (struct ef4_tx_queue*) ; 
 int EF4_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EF4_TXQ_TYPES ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_SUBDATA ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_farch_magic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ef4_tx_queue* ef4_get_tx_queue (struct ef4_nic*,int,int) ; 

__attribute__((used)) static void
ef4_farch_handle_tx_flush_done(struct ef4_nic *efx, ef4_qword_t *event)
{
	struct ef4_tx_queue *tx_queue;
	int qid;

	qid = EF4_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBDATA);
	if (qid < EF4_TXQ_TYPES * efx->n_tx_channels) {
		tx_queue = ef4_get_tx_queue(efx, qid / EF4_TXQ_TYPES,
					    qid % EF4_TXQ_TYPES);
		if (atomic_cmpxchg(&tx_queue->flush_outstanding, 1, 0)) {
			ef4_farch_magic_event(tx_queue->channel,
					      EF4_CHANNEL_MAGIC_TX_DRAIN(tx_queue));
		}
	}
}