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
struct fe_tx_ring {int /*<<< orphan*/ * tx_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  txd4; } ;
struct fe_map_state {size_t ring_idx; int /*<<< orphan*/  def_txd4; TYPE_1__ txd; } ;

/* Variables and functions */
 size_t NEXT_TX_DESP_IDX (size_t) ; 
 int /*<<< orphan*/  fe_set_txd (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fe_tx_dma_write_desc(struct fe_tx_ring *ring, struct fe_map_state *st)
{
	fe_set_txd(&st->txd, &ring->tx_dma[st->ring_idx]);
	memset(&st->txd, 0, sizeof(st->txd));
	st->txd.txd4 = st->def_txd4;
	st->ring_idx = NEXT_TX_DESP_IDX(st->ring_idx);
}