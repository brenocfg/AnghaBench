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
typedef  unsigned int u8 ;
struct pm3_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM3RD_IndexHigh ; 
 int /*<<< orphan*/  PM3RD_IndexLow ; 
 int /*<<< orphan*/  PM3RD_IndexedData ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void PM3_WRITE_DAC_REG(struct pm3_par *par, unsigned r, u8 v)
{
	PM3_WAIT(par, 3);
	PM3_WRITE_REG(par, PM3RD_IndexHigh, (r >> 8) & 0xff);
	PM3_WRITE_REG(par, PM3RD_IndexLow, r & 0xff);
	wmb();
	PM3_WRITE_REG(par, PM3RD_IndexedData, v);
	wmb();
}