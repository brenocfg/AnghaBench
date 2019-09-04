#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mt76x2_vif {int /*<<< orphan*/  group_wcid; } ;
struct mt76x2_sta {int /*<<< orphan*/  wcid; } ;
struct mt76x2_dev {int /*<<< orphan*/  mt76; } ;
struct mt76_txq {int /*<<< orphan*/ * wcid; } ;
struct ieee80211_txq {TYPE_1__* vif; TYPE_2__* sta; scalar_t__ drv_priv; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;
struct TYPE_3__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_txq_init (int /*<<< orphan*/ *,struct ieee80211_txq*) ; 

void mt76x2_txq_init(struct mt76x2_dev *dev, struct ieee80211_txq *txq)
{
	struct mt76_txq *mtxq;

	if (!txq)
		return;

	mtxq = (struct mt76_txq *) txq->drv_priv;
	if (txq->sta) {
		struct mt76x2_sta *sta;

		sta = (struct mt76x2_sta *) txq->sta->drv_priv;
		mtxq->wcid = &sta->wcid;
	} else {
		struct mt76x2_vif *mvif;

		mvif = (struct mt76x2_vif *) txq->vif->drv_priv;
		mtxq->wcid = &mvif->group_wcid;
	}

	mt76_txq_init(&dev->mt76, txq);
}