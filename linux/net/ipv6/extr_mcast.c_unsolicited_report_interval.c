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
struct TYPE_2__ {int mldv1_unsolicited_report_interval; int mldv2_unsolicited_report_interval; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 scalar_t__ mld_in_v1_mode (struct inet6_dev*) ; 

__attribute__((used)) static int unsolicited_report_interval(struct inet6_dev *idev)
{
	int iv;

	if (mld_in_v1_mode(idev))
		iv = idev->cnf.mldv1_unsolicited_report_interval;
	else
		iv = idev->cnf.mldv2_unsolicited_report_interval;

	return iv > 0 ? iv : 1;
}