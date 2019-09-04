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
struct inet6_dev {int /*<<< orphan*/  mc_qrv; int /*<<< orphan*/  mc_ifc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mld_ifc_start_timer (struct inet6_dev*,int) ; 
 scalar_t__ mld_in_v1_mode (struct inet6_dev*) ; 

__attribute__((used)) static void mld_ifc_event(struct inet6_dev *idev)
{
	if (mld_in_v1_mode(idev))
		return;
	idev->mc_ifc_count = idev->mc_qrv;
	mld_ifc_start_timer(idev, 1);
}