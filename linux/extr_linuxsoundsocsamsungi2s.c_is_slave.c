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
struct i2s_dai {TYPE_1__* variant_regs; scalar_t__ addr; } ;
struct TYPE_2__ {int mss_off; } ;

/* Variables and functions */
 scalar_t__ I2SMOD ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline bool is_slave(struct i2s_dai *i2s)
{
	u32 mod = readl(i2s->addr + I2SMOD);
	return (mod & (1 << i2s->variant_regs->mss_off)) ? true : false;
}