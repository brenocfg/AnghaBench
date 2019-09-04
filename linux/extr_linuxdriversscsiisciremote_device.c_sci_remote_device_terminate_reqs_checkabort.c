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
typedef  size_t u32 ;
struct isci_request {int dummy; } ;
struct isci_remote_device {TYPE_1__* owning_port; } ;
struct isci_host {struct isci_request** reqs; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
struct TYPE_2__ {struct isci_host* owning_controller; } ;

/* Variables and functions */
 size_t SCI_MAX_IO_REQUESTS ; 
 int SCI_SUCCESS ; 
 int sci_remote_device_terminate_req (struct isci_host*,struct isci_remote_device*,int,struct isci_request*) ; 

__attribute__((used)) static enum sci_status sci_remote_device_terminate_reqs_checkabort(
	struct isci_remote_device *idev,
	int chk)
{
	struct isci_host *ihost = idev->owning_port->owning_controller;
	enum sci_status status  = SCI_SUCCESS;
	u32 i;

	for (i = 0; i < SCI_MAX_IO_REQUESTS; i++) {
		struct isci_request *ireq = ihost->reqs[i];
		enum sci_status s;

		s = sci_remote_device_terminate_req(ihost, idev, chk, ireq);
		if (s != SCI_SUCCESS)
			status = s;
	}
	return status;
}