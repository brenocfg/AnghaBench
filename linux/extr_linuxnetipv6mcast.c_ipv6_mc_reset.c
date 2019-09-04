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
struct inet6_dev {int /*<<< orphan*/  mc_maxdelay; scalar_t__ mc_v1_seen; int /*<<< orphan*/  mc_qri; int /*<<< orphan*/  mc_qi; int /*<<< orphan*/  mc_qrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLD_QI_DEFAULT ; 
 int /*<<< orphan*/  MLD_QRI_DEFAULT ; 
 int /*<<< orphan*/  sysctl_mld_qrv ; 
 int /*<<< orphan*/  unsolicited_report_interval (struct inet6_dev*) ; 

__attribute__((used)) static void ipv6_mc_reset(struct inet6_dev *idev)
{
	idev->mc_qrv = sysctl_mld_qrv;
	idev->mc_qi = MLD_QI_DEFAULT;
	idev->mc_qri = MLD_QRI_DEFAULT;
	idev->mc_v1_seen = 0;
	idev->mc_maxdelay = unsolicited_report_interval(idev);
}