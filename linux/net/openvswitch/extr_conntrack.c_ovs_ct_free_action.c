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
struct ovs_conntrack_info {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ovs_ct_free_action (struct ovs_conntrack_info*) ; 
 struct ovs_conntrack_info* nla_data (struct nlattr const*) ; 

void ovs_ct_free_action(const struct nlattr *a)
{
	struct ovs_conntrack_info *ct_info = nla_data(a);

	__ovs_ct_free_action(ct_info);
}