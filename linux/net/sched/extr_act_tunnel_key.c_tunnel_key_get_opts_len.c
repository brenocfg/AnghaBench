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
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int tunnel_key_copy_opts (struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int tunnel_key_get_opts_len(struct nlattr *nla,
				   struct netlink_ext_ack *extack)
{
	return tunnel_key_copy_opts(nla, NULL, 0, extack);
}