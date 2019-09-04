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
typedef  scalar_t__ u32 ;
struct isci_remote_device {int /*<<< orphan*/  owning_port; int /*<<< orphan*/  flags; int /*<<< orphan*/  domain_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_RNC_LLHANG_ENABLED ; 
 scalar_t__ dev_is_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_port_set_hang_detection_timeout (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void isci_dev_set_hang_detection_timeout(
	struct isci_remote_device *idev,
	u32 timeout)
{
	if (dev_is_sata(idev->domain_dev)) {
		if (timeout) {
			if (test_and_set_bit(IDEV_RNC_LLHANG_ENABLED,
					     &idev->flags))
				return;  /* Already enabled. */
		} else if (!test_and_clear_bit(IDEV_RNC_LLHANG_ENABLED,
					       &idev->flags))
			return;  /* Not enabled. */

		sci_port_set_hang_detection_timeout(idev->owning_port,
						    timeout);
	}
}