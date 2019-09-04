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
struct nlattr {int dummy; } ;
struct datapath {int /*<<< orphan*/  user_features; } ;

/* Variables and functions */
 size_t OVS_DP_ATTR_USER_FEATURES ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static void ovs_dp_change(struct datapath *dp, struct nlattr *a[])
{
	if (a[OVS_DP_ATTR_USER_FEATURES])
		dp->user_features = nla_get_u32(a[OVS_DP_ATTR_USER_FEATURES]);
}