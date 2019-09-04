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
struct TYPE_2__ {int rfs_off; int rfs_mask; } ;

/* Variables and functions */
 scalar_t__ I2SMOD ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned get_rfs(struct i2s_dai *i2s)
{
	u32 rfs;
	rfs = readl(i2s->addr + I2SMOD) >> i2s->variant_regs->rfs_off;
	rfs &= i2s->variant_regs->rfs_mask;

	switch (rfs) {
	case 7: return 192;
	case 6: return 96;
	case 5: return 128;
	case 4: return 64;
	case 3:	return 768;
	case 2: return 384;
	case 1:	return 512;
	default: return 256;
	}
}