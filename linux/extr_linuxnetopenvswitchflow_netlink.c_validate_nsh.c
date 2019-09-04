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
struct sw_flow_match {int dummy; } ;
struct sw_flow_key {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int nsh_key_put_from_nlattr (struct nlattr const*,struct sw_flow_match*,int,int,int) ; 
 int /*<<< orphan*/  ovs_match_init (struct sw_flow_match*,struct sw_flow_key*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool validate_nsh(const struct nlattr *attr, bool is_mask,
			 bool is_push_nsh, bool log)
{
	struct sw_flow_match match;
	struct sw_flow_key key;
	int ret = 0;

	ovs_match_init(&match, &key, true, NULL);
	ret = nsh_key_put_from_nlattr(attr, &match, is_mask,
				      is_push_nsh, log);
	return !ret;
}