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
struct isci_request {int dummy; } ;
struct isci_remote_device {int /*<<< orphan*/  started_request_count; int /*<<< orphan*/  kref; struct isci_port* owning_port; } ;
struct isci_port {int dummy; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_port_complete_io (struct isci_port*,struct isci_remote_device*,struct isci_request*) ; 

__attribute__((used)) static void sci_remote_device_start_request(struct isci_remote_device *idev,
						 struct isci_request *ireq,
						 enum sci_status status)
{
	struct isci_port *iport = idev->owning_port;

	/* cleanup requests that failed after starting on the port */
	if (status != SCI_SUCCESS)
		sci_port_complete_io(iport, idev, ireq);
	else {
		kref_get(&idev->kref);
		idev->started_request_count++;
	}
}