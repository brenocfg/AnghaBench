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
struct sk_buff {int dummy; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_FLASH_UPDATE_COMPONENT ; 
 int /*<<< orphan*/  DEVLINK_ATTR_FLASH_UPDATE_STATUS_DONE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_FLASH_UPDATE_STATUS_MSG ; 
 int /*<<< orphan*/  DEVLINK_ATTR_FLASH_UPDATE_STATUS_TOTAL ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int DEVLINK_CMD_FLASH_UPDATE_STATUS ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_flash_update_fill(struct sk_buff *msg,
					struct devlink *devlink,
					enum devlink_command cmd,
					const char *status_msg,
					const char *component,
					unsigned long done, unsigned long total)
{
	void *hdr;

	hdr = genlmsg_put(msg, 0, 0, &devlink_nl_family, 0, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto nla_put_failure;

	if (cmd != DEVLINK_CMD_FLASH_UPDATE_STATUS)
		goto out;

	if (status_msg &&
	    nla_put_string(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_MSG,
			   status_msg))
		goto nla_put_failure;
	if (component &&
	    nla_put_string(msg, DEVLINK_ATTR_FLASH_UPDATE_COMPONENT,
			   component))
		goto nla_put_failure;
	if (nla_put_u64_64bit(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_DONE,
			      done, DEVLINK_ATTR_PAD))
		goto nla_put_failure;
	if (nla_put_u64_64bit(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_TOTAL,
			      total, DEVLINK_ATTR_PAD))
		goto nla_put_failure;

out:
	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}