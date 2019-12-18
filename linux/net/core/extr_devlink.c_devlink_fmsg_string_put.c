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
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_NUL_STRING ; 
 int devlink_fmsg_put_value (struct devlink_fmsg*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

int devlink_fmsg_string_put(struct devlink_fmsg *fmsg, const char *value)
{
	return devlink_fmsg_put_value(fmsg, value, strlen(value) + 1,
				      NLA_NUL_STRING);
}