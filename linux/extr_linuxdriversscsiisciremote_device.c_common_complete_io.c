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
struct isci_remote_device {int dummy; } ;
struct isci_port {int dummy; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 int sci_port_complete_io (struct isci_port*,struct isci_remote_device*,struct isci_request*) ; 
 int /*<<< orphan*/  sci_remote_device_decrement_request_count (struct isci_remote_device*) ; 
 int sci_request_complete (struct isci_request*) ; 

__attribute__((used)) static enum sci_status common_complete_io(struct isci_port *iport,
					  struct isci_remote_device *idev,
					  struct isci_request *ireq)
{
	enum sci_status status;

	status = sci_request_complete(ireq);
	if (status != SCI_SUCCESS)
		return status;

	status = sci_port_complete_io(iport, idev, ireq);
	if (status != SCI_SUCCESS)
		return status;

	sci_remote_device_decrement_request_count(idev);
	return status;
}