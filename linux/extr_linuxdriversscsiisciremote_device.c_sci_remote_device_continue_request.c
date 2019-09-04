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
struct isci_remote_device {scalar_t__ working_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_controller_continue_io (scalar_t__) ; 

__attribute__((used)) static void sci_remote_device_continue_request(void *dev)
{
	struct isci_remote_device *idev = dev;

	/* we need to check if this request is still valid to continue. */
	if (idev->working_request)
		sci_controller_continue_io(idev->working_request);
}