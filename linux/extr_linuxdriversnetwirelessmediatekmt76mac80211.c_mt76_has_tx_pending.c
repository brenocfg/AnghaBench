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
struct mt76_dev {TYPE_1__* q_tx; } ;
struct TYPE_2__ {scalar_t__ queued; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 

__attribute__((used)) static bool mt76_has_tx_pending(struct mt76_dev *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dev->q_tx); i++) {
		if (dev->q_tx[i].queued)
			return true;
	}

	return false;
}