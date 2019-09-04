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
struct TYPE_2__ {int flags; } ;
struct smsc911x_data {scalar_t__ ioaddr; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SMSC911X_USE_16BIT ; 
 int SMSC911X_USE_32BIT ; 
 scalar_t__ __smsc_shift (struct smsc911x_data*,int) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static inline u32
__smsc911x_reg_read_shift(struct smsc911x_data *pdata, u32 reg)
{
	if (pdata->config.flags & SMSC911X_USE_32BIT)
		return readl(pdata->ioaddr + __smsc_shift(pdata, reg));

	if (pdata->config.flags & SMSC911X_USE_16BIT)
		return (readw(pdata->ioaddr +
				__smsc_shift(pdata, reg)) & 0xFFFF) |
			((readw(pdata->ioaddr +
			__smsc_shift(pdata, reg + 2)) & 0xFFFF) << 16);

	BUG();
	return 0;
}