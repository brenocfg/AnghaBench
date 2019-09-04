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
struct intel_scu_ipc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ipc_read_status (struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int busy_loop(struct intel_scu_ipc_dev *scu)
{
	u32 status = ipc_read_status(scu);
	u32 loop_count = 100000;

	/* break if scu doesn't reset busy bit after huge retry */
	while ((status & BIT(0)) && --loop_count) {
		udelay(1); /* scu processing time is in few u secods */
		status = ipc_read_status(scu);
	}

	if (status & BIT(0)) {
		dev_err(scu->dev, "IPC timed out");
		return -ETIMEDOUT;
	}

	if (status & BIT(1))
		return -EIO;

	return 0;
}