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
struct psample_group {int /*<<< orphan*/  seq; int /*<<< orphan*/  refcount; int /*<<< orphan*/  group_num; } ;
typedef  enum psample_command { ____Placeholder_psample_command } psample_command ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_GROUP_REFCOUNT ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_GROUP_SEQ ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_SAMPLE_GROUP ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psample_nl_family ; 

__attribute__((used)) static int psample_group_nl_fill(struct sk_buff *msg,
				 struct psample_group *group,
				 enum psample_command cmd, u32 portid, u32 seq,
				 int flags)
{
	void *hdr;
	int ret;

	hdr = genlmsg_put(msg, portid, seq, &psample_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_SAMPLE_GROUP, group->group_num);
	if (ret < 0)
		goto error;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_GROUP_REFCOUNT, group->refcount);
	if (ret < 0)
		goto error;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_GROUP_SEQ, group->seq);
	if (ret < 0)
		goto error;

	genlmsg_end(msg, hdr);
	return 0;

error:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}