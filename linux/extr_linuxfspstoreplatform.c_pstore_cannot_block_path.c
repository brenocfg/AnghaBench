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
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;

/* Variables and functions */
#define  KMSG_DUMP_EMERG 129 
#define  KMSG_DUMP_PANIC 128 
 scalar_t__ in_nmi () ; 

bool pstore_cannot_block_path(enum kmsg_dump_reason reason)
{
	/*
	 * In case of NMI path, pstore shouldn't be blocked
	 * regardless of reason.
	 */
	if (in_nmi())
		return true;

	switch (reason) {
	/* In panic case, other cpus are stopped by smp_send_stop(). */
	case KMSG_DUMP_PANIC:
	/* Emergency restart shouldn't be blocked by spin lock. */
	case KMSG_DUMP_EMERG:
		return true;
	default:
		return false;
	}
}