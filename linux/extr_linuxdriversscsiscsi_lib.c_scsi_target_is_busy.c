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
struct scsi_target {scalar_t__ can_queue; int /*<<< orphan*/  target_blocked; int /*<<< orphan*/  target_busy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool scsi_target_is_busy(struct scsi_target *starget)
{
	if (starget->can_queue > 0) {
		if (atomic_read(&starget->target_busy) >= starget->can_queue)
			return true;
		if (atomic_read(&starget->target_blocked) > 0)
			return true;
	}
	return false;
}