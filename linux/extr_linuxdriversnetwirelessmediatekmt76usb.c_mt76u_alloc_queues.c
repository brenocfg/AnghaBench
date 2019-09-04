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
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int mt76u_alloc_rx (struct mt76_dev*) ; 
 int mt76u_alloc_tx (struct mt76_dev*) ; 

int mt76u_alloc_queues(struct mt76_dev *dev)
{
	int err;

	err = mt76u_alloc_rx(dev);
	if (err < 0)
		return err;

	return mt76u_alloc_tx(dev);
}