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
struct inet6_dev {scalar_t__ mc_dad_count; scalar_t__ mc_qrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mld_dad_start_timer (struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_send_initial_cr (struct inet6_dev*) ; 
 int /*<<< orphan*/  unsolicited_report_interval (struct inet6_dev*) ; 

void ipv6_mc_dad_complete(struct inet6_dev *idev)
{
	idev->mc_dad_count = idev->mc_qrv;
	if (idev->mc_dad_count) {
		mld_send_initial_cr(idev);
		idev->mc_dad_count--;
		if (idev->mc_dad_count)
			mld_dad_start_timer(idev,
					    unsolicited_report_interval(idev));
	}
}