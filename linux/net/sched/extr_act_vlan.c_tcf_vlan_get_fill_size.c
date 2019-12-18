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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tc_vlan {int dummy; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t tcf_vlan_get_fill_size(const struct tc_action *act)
{
	return nla_total_size(sizeof(struct tc_vlan))
		+ nla_total_size(sizeof(u16)) /* TCA_VLAN_PUSH_VLAN_ID */
		+ nla_total_size(sizeof(u16)) /* TCA_VLAN_PUSH_VLAN_PROTOCOL */
		+ nla_total_size(sizeof(u8)); /* TCA_VLAN_PUSH_VLAN_PRIORITY */
}