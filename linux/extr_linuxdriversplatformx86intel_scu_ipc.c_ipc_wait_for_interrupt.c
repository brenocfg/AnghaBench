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
struct intel_scu_ipc_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_complete; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ipc_read_status (struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int ipc_wait_for_interrupt(struct intel_scu_ipc_dev *scu)
{
	int status;

	if (!wait_for_completion_timeout(&scu->cmd_complete, 3 * HZ)) {
		dev_err(scu->dev, "IPC timed out\n");
		return -ETIMEDOUT;
	}

	status = ipc_read_status(scu);
	if (status & BIT(1))
		return -EIO;

	return 0;
}