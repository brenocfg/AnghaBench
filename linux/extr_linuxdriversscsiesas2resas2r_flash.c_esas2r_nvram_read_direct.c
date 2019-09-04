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
struct esas2r_sas_nvram {int dummy; } ;
struct esas2r_adapter {int /*<<< orphan*/  nvram_semaphore; int /*<<< orphan*/  nvram; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLS_OFFSET_NVR ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int esas2r_nvram_validate (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_read_flash_block (struct esas2r_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

bool esas2r_nvram_read_direct(struct esas2r_adapter *a)
{
	bool result;

	if (down_interruptible(&a->nvram_semaphore))
		return false;

	if (!esas2r_read_flash_block(a, a->nvram, FLS_OFFSET_NVR,
				     sizeof(struct esas2r_sas_nvram))) {
		esas2r_hdebug("NVRAM read failed, using defaults");
		return false;
	}

	result = esas2r_nvram_validate(a);

	up(&a->nvram_semaphore);

	return result;
}