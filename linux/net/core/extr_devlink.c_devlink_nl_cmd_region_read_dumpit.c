#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/ * args; TYPE_1__* nlh; TYPE_5__* skb; int /*<<< orphan*/  extack; } ;
struct devlink_region {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  sk; } ;
struct TYPE_8__ {int /*<<< orphan*/  portid; } ;
struct TYPE_7__ {int /*<<< orphan*/  policy; scalar_t__ hdrsize; } ;
struct TYPE_6__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_ATTR_MAX ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_CHUNKS ; 
 size_t DEVLINK_ATTR_REGION_CHUNK_ADDR ; 
 size_t DEVLINK_ATTR_REGION_CHUNK_LEN ; 
 size_t DEVLINK_ATTR_REGION_NAME ; 
 size_t DEVLINK_ATTR_REGION_SNAPSHOT_ID ; 
 int /*<<< orphan*/  DEVLINK_CMD_REGION_READ ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 scalar_t__ GENL_HDRLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devlink*) ; 
 TYPE_4__ NETLINK_CB (TYPE_5__*) ; 
 int NLM_F_ACK ; 
 int NLM_F_MULTI ; 
 int PTR_ERR (struct devlink*) ; 
 struct devlink* devlink_get_from_attrs (int /*<<< orphan*/ ,struct nlattr**) ; 
 int /*<<< orphan*/  devlink_mutex ; 
 TYPE_2__ devlink_nl_family ; 
 int devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int devlink_nl_region_read_snapshot_fill (struct sk_buff*,struct devlink*,struct devlink_region*,struct nlattr**,scalar_t__,scalar_t__,int,scalar_t__*) ; 
 struct devlink_region* devlink_region_get_by_name (struct devlink*,char const*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nlattr**) ; 
 struct nlattr** kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char* nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u64 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nla_put_string (struct sk_buff*,size_t,char const*) ; 
 int nlmsg_parse_deprecated (TYPE_1__*,scalar_t__,struct nlattr**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_region_read_dumpit(struct sk_buff *skb,
					     struct netlink_callback *cb)
{
	u64 ret_offset, start_offset, end_offset = 0;
	struct devlink_region *region;
	struct nlattr *chunks_attr;
	const char *region_name;
	struct devlink *devlink;
	struct nlattr **attrs;
	bool dump = true;
	void *hdr;
	int err;

	start_offset = *((u64 *)&cb->args[0]);

	attrs = kmalloc_array(DEVLINK_ATTR_MAX + 1, sizeof(*attrs), GFP_KERNEL);
	if (!attrs)
		return -ENOMEM;

	err = nlmsg_parse_deprecated(cb->nlh,
				     GENL_HDRLEN + devlink_nl_family.hdrsize,
				     attrs, DEVLINK_ATTR_MAX,
				     devlink_nl_family.policy, cb->extack);
	if (err)
		goto out_free;

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_attrs(sock_net(cb->skb->sk), attrs);
	if (IS_ERR(devlink)) {
		err = PTR_ERR(devlink);
		goto out_dev;
	}

	mutex_lock(&devlink->lock);

	if (!attrs[DEVLINK_ATTR_REGION_NAME] ||
	    !attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]) {
		err = -EINVAL;
		goto out_unlock;
	}

	region_name = nla_data(attrs[DEVLINK_ATTR_REGION_NAME]);
	region = devlink_region_get_by_name(devlink, region_name);
	if (!region) {
		err = -EINVAL;
		goto out_unlock;
	}

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &devlink_nl_family, NLM_F_ACK | NLM_F_MULTI,
			  DEVLINK_CMD_REGION_READ);
	if (!hdr) {
		err = -EMSGSIZE;
		goto out_unlock;
	}

	err = devlink_nl_put_handle(skb, devlink);
	if (err)
		goto nla_put_failure;

	err = nla_put_string(skb, DEVLINK_ATTR_REGION_NAME, region_name);
	if (err)
		goto nla_put_failure;

	chunks_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_REGION_CHUNKS);
	if (!chunks_attr) {
		err = -EMSGSIZE;
		goto nla_put_failure;
	}

	if (attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR] &&
	    attrs[DEVLINK_ATTR_REGION_CHUNK_LEN]) {
		if (!start_offset)
			start_offset =
				nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR]);

		end_offset = nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR]);
		end_offset += nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_LEN]);
		dump = false;
	}

	err = devlink_nl_region_read_snapshot_fill(skb, devlink,
						   region, attrs,
						   start_offset,
						   end_offset, dump,
						   &ret_offset);

	if (err && err != -EMSGSIZE)
		goto nla_put_failure;

	/* Check if there was any progress done to prevent infinite loop */
	if (ret_offset == start_offset) {
		err = -EINVAL;
		goto nla_put_failure;
	}

	*((u64 *)&cb->args[0]) = ret_offset;

	nla_nest_end(skb, chunks_attr);
	genlmsg_end(skb, hdr);
	mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);
	kfree(attrs);

	return skb->len;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
out_unlock:
	mutex_unlock(&devlink->lock);
out_dev:
	mutex_unlock(&devlink_mutex);
out_free:
	kfree(attrs);
	return err;
}