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
typedef  int u64 ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MSR_OC_MAILBOX ; 
 int /*<<< orphan*/  MSR_OC_MAILBOX_BUSY_BIT ; 
 int MSR_OC_MAILBOX_CMD_OFFSET ; 
 int MSR_OC_MAILBOX_RSP_OFFSET ; 
 int OC_MAILBOX_FC_CONTROL_CMD ; 
 int OC_MAILBOX_RETRY_COUNT ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,...) ; 
 int rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int wrmsrl_safe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_oc_core_priority(unsigned int cpu)
{
	u64 value, cmd = OC_MAILBOX_FC_CONTROL_CMD;
	int ret, i;

	/* Issue favored core read command */
	value = cmd << MSR_OC_MAILBOX_CMD_OFFSET;
	/* Set the busy bit to indicate OS is trying to issue command */
	value |=  BIT_ULL(MSR_OC_MAILBOX_BUSY_BIT);
	ret = wrmsrl_safe(MSR_OC_MAILBOX, value);
	if (ret) {
		pr_debug("cpu %d OC mailbox write failed\n", cpu);
		return ret;
	}

	for (i = 0; i < OC_MAILBOX_RETRY_COUNT; ++i) {
		ret = rdmsrl_safe(MSR_OC_MAILBOX, &value);
		if (ret) {
			pr_debug("cpu %d OC mailbox read failed\n", cpu);
			break;
		}

		if (value & BIT_ULL(MSR_OC_MAILBOX_BUSY_BIT)) {
			pr_debug("cpu %d OC mailbox still processing\n", cpu);
			ret = -EBUSY;
			continue;
		}

		if ((value >> MSR_OC_MAILBOX_RSP_OFFSET) & 0xff) {
			pr_debug("cpu %d OC mailbox cmd failed\n", cpu);
			ret = -ENXIO;
			break;
		}

		ret = value & 0xff;
		pr_debug("cpu %d max_ratio %d\n", cpu, ret);
		break;
	}

	return ret;
}