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
struct iwl_rxq {int /*<<< orphan*/  rx_used; } ;
struct iwl_rb_allocator {int /*<<< orphan*/  lock; int /*<<< orphan*/  rbd_empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_rx_move_to_allocator(struct iwl_rxq *rxq,
					  struct iwl_rb_allocator *rba)
{
	spin_lock(&rba->lock);
	list_splice_tail_init(&rxq->rx_used, &rba->rbd_empty);
	spin_unlock(&rba->lock);
}