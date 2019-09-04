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
typedef  int /*<<< orphan*/  u64 ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_device {int generation; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  node_id; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  ERROR_RETRY_DELAY_MS ; 
 unsigned int FW_FIXED_GENERATION ; 
 unsigned int FW_GENERATION_MASK ; 
 unsigned int FW_QUIET ; 
 int RCODE_COMPLETE ; 
 int RCODE_GENERATION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  fw_rcode_string (int) ; 
 int fw_run_transaction (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ rcode_is_permanent_error (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 

int snd_fw_transaction(struct fw_unit *unit, int tcode,
		       u64 offset, void *buffer, size_t length,
		       unsigned int flags)
{
	struct fw_device *device = fw_parent_device(unit);
	int generation, rcode, tries = 0;

	generation = flags & FW_GENERATION_MASK;
	for (;;) {
		if (!(flags & FW_FIXED_GENERATION)) {
			generation = device->generation;
			smp_rmb(); /* node_id vs. generation */
		}
		rcode = fw_run_transaction(device->card, tcode,
					   device->node_id, generation,
					   device->max_speed, offset,
					   buffer, length);

		if (rcode == RCODE_COMPLETE)
			return 0;

		if (rcode == RCODE_GENERATION && (flags & FW_FIXED_GENERATION))
			return -EAGAIN;

		if (rcode_is_permanent_error(rcode) || ++tries >= 3) {
			if (!(flags & FW_QUIET))
				dev_err(&unit->device,
					"transaction failed: %s\n",
					fw_rcode_string(rcode));
			return -EIO;
		}

		msleep(ERROR_RETRY_DELAY_MS);
	}
}