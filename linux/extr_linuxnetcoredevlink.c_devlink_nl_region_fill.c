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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct devlink_region {int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_SIZE ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 int devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int devlink_nl_region_snapshots_id_put (struct sk_buff*,struct devlink*,struct devlink_region*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_region_fill(struct sk_buff *msg, struct devlink *devlink,
				  enum devlink_command cmd, u32 portid,
				  u32 seq, int flags,
				  struct devlink_region *region)
{
	void *hdr;
	int err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	err = devlink_nl_put_handle(msg, devlink);
	if (err)
		goto nla_put_failure;

	err = nla_put_string(msg, DEVLINK_ATTR_REGION_NAME, region->name);
	if (err)
		goto nla_put_failure;

	err = nla_put_u64_64bit(msg, DEVLINK_ATTR_REGION_SIZE,
				region->size,
				DEVLINK_ATTR_PAD);
	if (err)
		goto nla_put_failure;

	err = devlink_nl_region_snapshots_id_put(msg, devlink, region);
	if (err)
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return err;
}