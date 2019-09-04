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
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static inline int ovs_ct_copy_action(struct net *net, const struct nlattr *nla,
				     const struct sw_flow_key *key,
				     struct sw_flow_actions **acts, bool log)
{
	return -ENOTSUPP;
}