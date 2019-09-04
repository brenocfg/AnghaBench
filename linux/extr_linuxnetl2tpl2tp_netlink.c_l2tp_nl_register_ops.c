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
struct l2tp_nl_cmd_ops {int dummy; } ;
typedef  enum l2tp_pwtype { ____Placeholder_l2tp_pwtype } l2tp_pwtype ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int __L2TP_PWTYPE_MAX ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 struct l2tp_nl_cmd_ops const** l2tp_nl_cmd_ops ; 

int l2tp_nl_register_ops(enum l2tp_pwtype pw_type, const struct l2tp_nl_cmd_ops *ops)
{
	int ret;

	ret = -EINVAL;
	if (pw_type >= __L2TP_PWTYPE_MAX)
		goto err;

	genl_lock();
	ret = -EBUSY;
	if (l2tp_nl_cmd_ops[pw_type])
		goto out;

	l2tp_nl_cmd_ops[pw_type] = ops;
	ret = 0;

out:
	genl_unlock();
err:
	return ret;
}