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
struct Scsi_Host {int eh_deadline; scalar_t__ last_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int scsi_host_eh_past_deadline(struct Scsi_Host *shost)
{
	if (!shost->last_reset || shost->eh_deadline == -1)
		return 0;

	/*
	 * 32bit accesses are guaranteed to be atomic
	 * (on all supported architectures), so instead
	 * of using a spinlock we can as well double check
	 * if eh_deadline has been set to 'off' during the
	 * time_before call.
	 */
	if (time_before(jiffies, shost->last_reset + shost->eh_deadline) &&
	    shost->eh_deadline > -1)
		return 0;

	return 1;
}