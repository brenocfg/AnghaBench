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
struct devlink_info_req {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_INFO_VERSION_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_INFO_VERSION_VALUE ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int) ; 
 int nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int devlink_info_version_put(struct devlink_info_req *req, int attr,
				    const char *version_name,
				    const char *version_value)
{
	struct nlattr *nest;
	int err;

	nest = nla_nest_start_noflag(req->msg, attr);
	if (!nest)
		return -EMSGSIZE;

	err = nla_put_string(req->msg, DEVLINK_ATTR_INFO_VERSION_NAME,
			     version_name);
	if (err)
		goto nla_put_failure;

	err = nla_put_string(req->msg, DEVLINK_ATTR_INFO_VERSION_VALUE,
			     version_value);
	if (err)
		goto nla_put_failure;

	nla_nest_end(req->msg, nest);

	return 0;

nla_put_failure:
	nla_nest_cancel(req->msg, nest);
	return err;
}