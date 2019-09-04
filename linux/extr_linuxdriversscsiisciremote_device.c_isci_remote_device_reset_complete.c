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
struct isci_remote_device {int dummy; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int sci_remote_device_reset_complete (struct isci_remote_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

enum sci_status isci_remote_device_reset_complete(
	struct isci_host *ihost,
	struct isci_remote_device *idev)
{
	unsigned long flags;
	enum sci_status status;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	status = sci_remote_device_reset_complete(idev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	return status;
}