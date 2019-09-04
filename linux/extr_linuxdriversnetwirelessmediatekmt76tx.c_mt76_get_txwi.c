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
struct mt76_txwi_cache {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 struct mt76_txwi_cache* __mt76_get_txwi (struct mt76_dev*) ; 
 struct mt76_txwi_cache* mt76_alloc_txwi (struct mt76_dev*) ; 

struct mt76_txwi_cache *
mt76_get_txwi(struct mt76_dev *dev)
{
	struct mt76_txwi_cache *t = __mt76_get_txwi(dev);

	if (t)
		return t;

	return mt76_alloc_txwi(dev);
}