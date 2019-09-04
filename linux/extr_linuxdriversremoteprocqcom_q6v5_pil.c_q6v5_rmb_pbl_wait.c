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
struct q6v5 {scalar_t__ rmb_base; } ;
typedef  int s32 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ RMB_PBL_STATUS_REG ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int q6v5_rmb_pbl_wait(struct q6v5 *qproc, int ms)
{
	unsigned long timeout;
	s32 val;

	timeout = jiffies + msecs_to_jiffies(ms);
	for (;;) {
		val = readl(qproc->rmb_base + RMB_PBL_STATUS_REG);
		if (val)
			break;

		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;

		msleep(1);
	}

	return val;
}