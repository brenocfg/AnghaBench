#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct airo_info {int* fids; TYPE_1__* dev; TYPE_1__* wifidev; int /*<<< orphan*/  flags; int /*<<< orphan*/  aux_lock; int /*<<< orphan*/  txq; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVACK ; 
 int EV_TX ; 
 int EV_TXCPY ; 
 int EV_TXEXC ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int /*<<< orphan*/  FLAG_PENDING_XMIT ; 
 int /*<<< orphan*/  FLAG_PENDING_XMIT11 ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int MAX_FIDS ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TXCOMPLFID ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tx_error (struct airo_info*,int) ; 
 int /*<<< orphan*/  mpi_send_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_handle_tx(struct airo_info *ai, u16 status)
{
	int i, index = -1;
	u16 fid;

	if (test_bit(FLAG_MPI, &ai->flags)) {
		unsigned long flags;

		if (status & EV_TXEXC)
			get_tx_error(ai, -1);

		spin_lock_irqsave(&ai->aux_lock, flags);
		if (!skb_queue_empty(&ai->txq)) {
			spin_unlock_irqrestore(&ai->aux_lock,flags);
			mpi_send_packet(ai->dev);
		} else {
			clear_bit(FLAG_PENDING_XMIT, &ai->flags);
			spin_unlock_irqrestore(&ai->aux_lock,flags);
			netif_wake_queue(ai->dev);
		}
		OUT4500(ai, EVACK, status & (EV_TX | EV_TXCPY | EV_TXEXC));
		return;
	}

	fid = IN4500(ai, TXCOMPLFID);

	for (i = 0; i < MAX_FIDS; i++) {
		if ((ai->fids[i] & 0xffff) == fid)
			index = i;
	}

	if (index != -1) {
		if (status & EV_TXEXC)
			get_tx_error(ai, index);

		OUT4500(ai, EVACK, status & (EV_TX | EV_TXEXC));

		/* Set up to be used again */
		ai->fids[index] &= 0xffff;
		if (index < MAX_FIDS / 2) {
			if (!test_bit(FLAG_PENDING_XMIT, &ai->flags))
				netif_wake_queue(ai->dev);
		} else {
			if (!test_bit(FLAG_PENDING_XMIT11, &ai->flags))
				netif_wake_queue(ai->wifidev);
		}
	} else {
		OUT4500(ai, EVACK, status & (EV_TX | EV_TXCPY | EV_TXEXC));
		airo_print_err(ai->dev->name, "Unallocated FID was used to xmit");
	}
}