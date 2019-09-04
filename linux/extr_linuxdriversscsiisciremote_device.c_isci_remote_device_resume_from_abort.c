#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  user_cookie; int /*<<< orphan*/  user_callback; } ;
struct isci_remote_device {int /*<<< orphan*/  flags; TYPE_1__ rnc; int /*<<< orphan*/  abort_resume_cbparam; int /*<<< orphan*/  abort_resume_cb; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_ABORT_PATH_ACTIVE ; 
 int /*<<< orphan*/  IDEV_ABORT_PATH_RESUME_PENDING ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isci_remote_device_resume_from_abort_complete ; 
 int /*<<< orphan*/  isci_remote_device_wait_for_resume_from_abort (struct isci_host*,struct isci_remote_device*) ; 
 int sci_remote_device_resume (struct isci_remote_device*,int /*<<< orphan*/ ,struct isci_remote_device*) ; 
 int sci_remote_node_context_is_being_destroyed (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

enum sci_status isci_remote_device_resume_from_abort(
	struct isci_host *ihost,
	struct isci_remote_device *idev)
{
	unsigned long flags;
	enum sci_status status = SCI_SUCCESS;
	int destroyed;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	/* Preserve any current resume callbacks, for instance from other
	 * resumptions.
	 */
	idev->abort_resume_cb = idev->rnc.user_callback;
	idev->abort_resume_cbparam = idev->rnc.user_cookie;
	set_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);
	clear_bit(IDEV_ABORT_PATH_ACTIVE, &idev->flags);
	destroyed = sci_remote_node_context_is_being_destroyed(&idev->rnc);
	if (!destroyed)
		status = sci_remote_device_resume(
			idev, isci_remote_device_resume_from_abort_complete,
			idev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
	if (!destroyed && (status == SCI_SUCCESS))
		isci_remote_device_wait_for_resume_from_abort(ihost, idev);
	else
		clear_bit(IDEV_ABORT_PATH_RESUME_PENDING, &idev->flags);

	return status;
}