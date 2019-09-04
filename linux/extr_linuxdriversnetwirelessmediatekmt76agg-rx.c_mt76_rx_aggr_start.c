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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mt76_wcid {int /*<<< orphan*/ * aggr; } ;
struct mt76_rx_tid {size_t size; int /*<<< orphan*/  lock; int /*<<< orphan*/  reorder_work; int /*<<< orphan*/  head; struct mt76_dev* dev; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mt76_rx_tid* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rx_aggr_reorder_work ; 
 int /*<<< orphan*/  mt76_rx_aggr_stop (struct mt76_dev*,struct mt76_wcid*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct mt76_rx_tid*) ; 
 int /*<<< orphan*/  reorder_buf ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct mt76_rx_tid*,int /*<<< orphan*/ ,size_t) ; 

int mt76_rx_aggr_start(struct mt76_dev *dev, struct mt76_wcid *wcid, u8 tidno,
		       u16 ssn, u8 size)
{
	struct mt76_rx_tid *tid;

	mt76_rx_aggr_stop(dev, wcid, tidno);

	tid = kzalloc(struct_size(tid, reorder_buf, size), GFP_KERNEL);
	if (!tid)
		return -ENOMEM;

	tid->dev = dev;
	tid->head = ssn;
	tid->size = size;
	INIT_DELAYED_WORK(&tid->reorder_work, mt76_rx_aggr_reorder_work);
	spin_lock_init(&tid->lock);

	rcu_assign_pointer(wcid->aggr[tidno], tid);

	return 0;
}