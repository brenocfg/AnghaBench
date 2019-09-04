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
typedef  unsigned int u32 ;
struct radeonfb_info {int dummy; } ;

/* Variables and functions */
 unsigned int __INPLL (struct radeonfb_info*,unsigned int) ; 
 int /*<<< orphan*/  __OUTPLL (struct radeonfb_info*,unsigned int,unsigned int) ; 

void __OUTPLLP(struct radeonfb_info *rinfo, unsigned int index,
			     u32 val, u32 mask)
{
	unsigned int tmp;

	tmp  = __INPLL(rinfo, index);
	tmp &= (mask);
	tmp |= (val);
	__OUTPLL(rinfo, index, tmp);
}