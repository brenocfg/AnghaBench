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
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sclp_early_wait_irq () ; 
 int sclp_service_call (int /*<<< orphan*/ ,void*) ; 

int sclp_early_cmd(sclp_cmdw_t cmd, void *sccb)
{
	unsigned long flags;
	int rc;

	raw_local_irq_save(flags);
	rc = sclp_service_call(cmd, sccb);
	if (rc)
		goto out;
	sclp_early_wait_irq();
out:
	raw_local_irq_restore(flags);
	return rc;
}