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
struct iwl_rxq {scalar_t__ used_count; scalar_t__ free_count; int /*<<< orphan*/  rx_used; int /*<<< orphan*/  rx_free; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_pcie_rx_init_rxb_lists(struct iwl_rxq *rxq)
{
	lockdep_assert_held(&rxq->lock);

	INIT_LIST_HEAD(&rxq->rx_free);
	INIT_LIST_HEAD(&rxq->rx_used);
	rxq->free_count = 0;
	rxq->used_count = 0;
}