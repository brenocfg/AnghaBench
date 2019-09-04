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
struct isci_request {int /*<<< orphan*/  sm; } ;
struct isci_remote_device {struct isci_request* working_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_REQ_COMPLETED ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atapi_remote_device_resume_done(void *_dev)
{
	struct isci_remote_device *idev = _dev;
	struct isci_request *ireq = idev->working_request;

	sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
}