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
struct mt76_wcid {int dummy; } ;
struct mt76x2_sta {TYPE_1__* vif; struct mt76_wcid wcid; } ;
struct mt76x2_dev {int dummy; } ;
struct TYPE_2__ {struct mt76_wcid group_wcid; } ;

/* Variables and functions */

__attribute__((used)) static struct mt76_wcid *
mt76x2_rx_get_sta_wcid(struct mt76x2_dev *dev, struct mt76x2_sta *sta,
		       bool unicast)
{
	if (!sta)
		return NULL;

	if (unicast)
		return &sta->wcid;
	else
		return &sta->vif->group_wcid;
}