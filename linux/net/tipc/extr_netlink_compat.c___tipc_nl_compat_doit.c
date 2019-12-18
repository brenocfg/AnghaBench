#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tipc_nl_compat_msg {int /*<<< orphan*/  dst_sk; } ;
struct tipc_nl_compat_cmd_doit {int (* transcode ) (struct tipc_nl_compat_cmd_doit*,struct sk_buff*,struct tipc_nl_compat_msg*) ;int (* doit ) (struct sk_buff*,struct genl_info*) ;} ;
struct sk_buff {int /*<<< orphan*/  sk; int /*<<< orphan*/  len; scalar_t__ data; } ;
struct nlattr {int dummy; } ;
struct genl_info {struct nlattr** attrs; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {scalar_t__ maxattr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nlattr**) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nlattr** kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct genl_info*,int /*<<< orphan*/ ,int) ; 
 int nla_parse_deprecated (struct nlattr**,scalar_t__,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct tipc_nl_compat_cmd_doit*,struct sk_buff*,struct tipc_nl_compat_msg*) ; 
 int stub2 (struct sk_buff*,struct genl_info*) ; 
 TYPE_1__ tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_compat_doit(struct tipc_nl_compat_cmd_doit *cmd,
				 struct tipc_nl_compat_msg *msg)
{
	int err;
	struct sk_buff *doit_buf;
	struct sk_buff *trans_buf;
	struct nlattr **attrbuf;
	struct genl_info info;

	trans_buf = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!trans_buf)
		return -ENOMEM;

	attrbuf = kmalloc_array(tipc_genl_family.maxattr + 1,
				sizeof(struct nlattr *),
				GFP_KERNEL);
	if (!attrbuf) {
		err = -ENOMEM;
		goto trans_out;
	}

	doit_buf = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!doit_buf) {
		err = -ENOMEM;
		goto attrbuf_out;
	}

	memset(&info, 0, sizeof(info));
	info.attrs = attrbuf;

	rtnl_lock();
	err = (*cmd->transcode)(cmd, trans_buf, msg);
	if (err)
		goto doit_out;

	err = nla_parse_deprecated(attrbuf, tipc_genl_family.maxattr,
				   (const struct nlattr *)trans_buf->data,
				   trans_buf->len, NULL, NULL);
	if (err)
		goto doit_out;

	doit_buf->sk = msg->dst_sk;

	err = (*cmd->doit)(doit_buf, &info);
doit_out:
	rtnl_unlock();

	kfree_skb(doit_buf);
attrbuf_out:
	kfree(attrbuf);
trans_out:
	kfree_skb(trans_buf);

	return err;
}