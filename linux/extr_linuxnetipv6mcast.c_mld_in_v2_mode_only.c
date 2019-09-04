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
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int mld_force_mld_version (struct inet6_dev const*) ; 

__attribute__((used)) static bool mld_in_v2_mode_only(const struct inet6_dev *idev)
{
	return mld_force_mld_version(idev) == 2;
}