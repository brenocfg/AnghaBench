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
struct sw_flow_actions {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct nlattr*) ; 
 struct nlattr* __add_action (struct sw_flow_actions**,int,void*,int,int) ; 

int ovs_nla_add_action(struct sw_flow_actions **sfa, int attrtype, void *data,
		       int len, bool log)
{
	struct nlattr *a;

	a = __add_action(sfa, attrtype, data, len, log);

	return PTR_ERR_OR_ZERO(a);
}