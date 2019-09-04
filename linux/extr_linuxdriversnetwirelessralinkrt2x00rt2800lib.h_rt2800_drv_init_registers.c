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
struct rt2x00_dev {TYPE_1__* ops; } ;
struct rt2800_ops {int (* drv_init_registers ) (struct rt2x00_dev*) ;} ;
struct TYPE_2__ {struct rt2800_ops* drv; } ;

/* Variables and functions */
 int stub1 (struct rt2x00_dev*) ; 

__attribute__((used)) static inline int rt2800_drv_init_registers(struct rt2x00_dev *rt2x00dev)
{
	const struct rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	return rt2800ops->drv_init_registers(rt2x00dev);
}