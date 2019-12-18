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
typedef  int u32 ;
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int sst_dsp_register_poll(struct sst_dsp *ctx, u32 offset, u32 mask,
			 u32 target, u32 time, char *operation)
{
	u32 reg;
	unsigned long timeout;
	int k = 0, s = 500;

	/*
	 * split the loop into sleeps of varying resolution. more accurately,
	 * the range of wakeups are:
	 * Phase 1(first 5ms): min sleep 0.5ms; max sleep 1ms.
	 * Phase 2:( 5ms to 10ms) : min sleep 0.5ms; max sleep 10ms
	 * (usleep_range (500, 1000) and usleep_range(5000, 10000) are
	 * both possible in this phase depending on whether k > 10 or not).
	 * Phase 3: (beyond 10 ms) min sleep 5ms; max sleep 10ms.
	 */

	timeout = jiffies + msecs_to_jiffies(time);
	while ((((reg = sst_dsp_shim_read_unlocked(ctx, offset)) & mask) != target)
		&& time_before(jiffies, timeout)) {
		k++;
		if (k > 10)
			s = 5000;

		usleep_range(s, 2*s);
	}

	if ((reg & mask) == target) {
		dev_dbg(ctx->dev, "FW Poll Status: reg=%#x %s successful\n",
					reg, operation);

		return 0;
	}

	dev_dbg(ctx->dev, "FW Poll Status: reg=%#x %s timedout\n",
					reg, operation);
	return -ETIME;
}