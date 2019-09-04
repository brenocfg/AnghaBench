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
struct wil_ring_tx_data {int dot1x_open; int /*<<< orphan*/  lock; scalar_t__ enabled; int /*<<< orphan*/  mid; } ;
struct wil_ring {int /*<<< orphan*/  va; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ring_fini_tx ) (struct wil6210_priv*,struct wil_ring*) ;} ;
struct wil6210_priv {TYPE_1__ txrx_ops; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  U8_MAX ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wil6210_priv*,struct wil_ring*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_status_napi_en ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void wil_ring_fini_tx(struct wil6210_priv *wil, int id)
{
	struct wil_ring *ring = &wil->ring_tx[id];
	struct wil_ring_tx_data *txdata = &wil->ring_tx_data[id];

	lockdep_assert_held(&wil->mutex);

	if (!ring->va)
		return;

	wil_dbg_misc(wil, "vring_fini_tx: id=%d\n", id);

	spin_lock_bh(&txdata->lock);
	txdata->dot1x_open = false;
	txdata->mid = U8_MAX;
	txdata->enabled = 0; /* no Tx can be in progress or start anew */
	spin_unlock_bh(&txdata->lock);
	/* napi_synchronize waits for completion of the current NAPI but will
	 * not prevent the next NAPI run.
	 * Add a memory barrier to guarantee that txdata->enabled is zeroed
	 * before napi_synchronize so that the next scheduled NAPI will not
	 * handle this vring
	 */
	wmb();
	/* make sure NAPI won't touch this vring */
	if (test_bit(wil_status_napi_en, wil->status))
		napi_synchronize(&wil->napi_tx);

	wil->txrx_ops.ring_fini_tx(wil, ring);
}