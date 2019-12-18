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
struct devlink_info_req {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_INFO_SERIAL_NUMBER ; 
 int nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int devlink_info_serial_number_put(struct devlink_info_req *req, const char *sn)
{
	return nla_put_string(req->msg, DEVLINK_ATTR_INFO_SERIAL_NUMBER, sn);
}