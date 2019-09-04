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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ suspend_count; } ;
struct isci_remote_device {TYPE_1__ rnc; } ;

/* Variables and functions */
 scalar_t__ sci_remote_node_context_is_being_destroyed (TYPE_1__*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static bool isci_compare_suspendcount(
	struct isci_remote_device *idev,
	u32 localcount)
{
	smp_rmb();

	/* Check for a change in the suspend count, or the RNC
	 * being destroyed.
	 */
	return (localcount != idev->rnc.suspend_count)
	    || sci_remote_node_context_is_being_destroyed(&idev->rnc);
}