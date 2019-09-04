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
struct ieee80211_txq {scalar_t__ drv_priv; } ;
struct ath10k_txq {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_txq_init(struct ieee80211_txq *txq)
{
	struct ath10k_txq *artxq;

	if (!txq)
		return;

	artxq = (void *)txq->drv_priv;
	INIT_LIST_HEAD(&artxq->list);
}