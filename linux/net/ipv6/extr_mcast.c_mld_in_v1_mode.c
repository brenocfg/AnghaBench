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
struct inet6_dev {scalar_t__ mc_v1_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ mld_in_v1_mode_only (struct inet6_dev const*) ; 
 scalar_t__ mld_in_v2_mode_only (struct inet6_dev const*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool mld_in_v1_mode(const struct inet6_dev *idev)
{
	if (mld_in_v2_mode_only(idev))
		return false;
	if (mld_in_v1_mode_only(idev))
		return true;
	if (idev->mc_v1_seen && time_before(jiffies, idev->mc_v1_seen))
		return true;

	return false;
}