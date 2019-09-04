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
struct esas2r_adapter {int dummy; } ;

/* Variables and functions */
 int DRBL_POWER_DOWN ; 
 int /*<<< orphan*/  MU_DOORBELL_IN ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esas2r_power_down_notify_firmware(struct esas2r_adapter *a)
{
	u32 starttime;
	u32 doorbell;

	esas2r_write_register_dword(a, MU_DOORBELL_IN, DRBL_POWER_DOWN);
	starttime = jiffies_to_msecs(jiffies);

	while (true) {
		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell & DRBL_POWER_DOWN) {
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);
			break;
		}

		schedule_timeout_interruptible(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - starttime) > 30000) {
			esas2r_hdebug("Timeout waiting for power down");
			break;
		}
	}
}