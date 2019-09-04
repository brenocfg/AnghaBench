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
struct isci_remote_device {int /*<<< orphan*/  rnc; int /*<<< orphan*/  flags; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_ABORT_PATH_RESUME_PENDING ; 
 int /*<<< orphan*/  IDEV_STOP_PENDING ; 
 scalar_t__ sci_remote_node_context_is_being_destroyed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool isci_remote_device_test_resume_done(
	struct isci_host *ihost,
	struct isci_remote_device *idev)
{
	unsigned long flags;
	bool done;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	done = !test_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags)
		|| test_bit(IDEV_STOP_PENDING, &idev->flags)
		|| sci_remote_node_context_is_being_destroyed(&idev->rnc);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	return done;
}