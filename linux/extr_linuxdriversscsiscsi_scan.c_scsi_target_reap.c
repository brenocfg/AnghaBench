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
struct scsi_target {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ STARGET_DEL ; 
 int /*<<< orphan*/  scsi_target_reap_ref_put (struct scsi_target*) ; 

void scsi_target_reap(struct scsi_target *starget)
{
	/*
	 * serious problem if this triggers: STARGET_DEL is only set in the if
	 * the reap_ref drops to zero, so we're trying to do another final put
	 * on an already released kref
	 */
	BUG_ON(starget->state == STARGET_DEL);
	scsi_target_reap_ref_put(starget);
}