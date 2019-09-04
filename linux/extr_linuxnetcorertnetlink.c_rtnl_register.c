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
typedef  int /*<<< orphan*/  rtnl_dumpit_func ;
typedef  int /*<<< orphan*/  rtnl_doit_func ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int rtnl_register_internal (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void rtnl_register(int protocol, int msgtype,
		   rtnl_doit_func doit, rtnl_dumpit_func dumpit,
		   unsigned int flags)
{
	int err;

	err = rtnl_register_internal(NULL, protocol, msgtype, doit, dumpit,
				     flags);
	if (err)
		pr_err("Unable to register rtnetlink message handler, "
		       "protocol = %d, message type = %d\n", protocol, msgtype);
}