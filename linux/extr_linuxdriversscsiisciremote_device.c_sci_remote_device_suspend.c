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
struct isci_remote_device {int /*<<< orphan*/  rnc; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
typedef  enum sci_remote_node_suspension_reasons { ____Placeholder_sci_remote_node_suspension_reasons } sci_remote_node_suspension_reasons ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT ; 
 int sci_remote_node_context_suspend (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

enum sci_status sci_remote_device_suspend(struct isci_remote_device *idev,
					  enum sci_remote_node_suspension_reasons reason)
{
	return sci_remote_node_context_suspend(&idev->rnc, reason,
					       SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT);
}