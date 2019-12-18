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
typedef  int u32 ;
struct i2s_dai {TYPE_1__* priv; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int CON_RXDMA_ACTIVE ; 
 scalar_t__ I2SCON ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline bool rx_active(struct i2s_dai *i2s)
{
	u32 active;

	if (!i2s)
		return false;

	active = readl(i2s->priv->addr + I2SCON) & CON_RXDMA_ACTIVE;

	return active ? true : false;
}