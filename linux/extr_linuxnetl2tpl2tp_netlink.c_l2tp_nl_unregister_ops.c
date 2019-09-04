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
typedef  enum l2tp_pwtype { ____Placeholder_l2tp_pwtype } l2tp_pwtype ;

/* Variables and functions */
 int __L2TP_PWTYPE_MAX ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int /*<<< orphan*/ ** l2tp_nl_cmd_ops ; 

void l2tp_nl_unregister_ops(enum l2tp_pwtype pw_type)
{
	if (pw_type < __L2TP_PWTYPE_MAX) {
		genl_lock();
		l2tp_nl_cmd_ops[pw_type] = NULL;
		genl_unlock();
	}
}