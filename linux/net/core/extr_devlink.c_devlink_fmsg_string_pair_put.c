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
 int devlink_fmsg_pair_nest_end (struct devlink_fmsg*) ; 
 int devlink_fmsg_pair_nest_start (struct devlink_fmsg*,char const*) ; 
 int devlink_fmsg_string_put (struct devlink_fmsg*,char const*) ; 

int devlink_fmsg_string_pair_put(struct devlink_fmsg *fmsg, const char *name,
				 const char *value)
{
	int err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	if (err)
		return err;

	err = devlink_fmsg_string_put(fmsg, value);
	if (err)
		return err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	if (err)
		return err;

	return 0;
}