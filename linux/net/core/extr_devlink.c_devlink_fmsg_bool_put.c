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
typedef  int /*<<< orphan*/  value ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_FLAG ; 
 int devlink_fmsg_put_value (struct devlink_fmsg*,int*,int,int /*<<< orphan*/ ) ; 

int devlink_fmsg_bool_put(struct devlink_fmsg *fmsg, bool value)
{
	return devlink_fmsg_put_value(fmsg, &value, sizeof(value), NLA_FLAG);
}