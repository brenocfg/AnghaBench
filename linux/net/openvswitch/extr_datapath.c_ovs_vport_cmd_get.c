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
struct vport {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ovs_header {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct ovs_header* userhdr; struct nlattr** attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_GET ; 
 int PTR_ERR (struct vport*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct vport* lookup_vport (int /*<<< orphan*/ ,struct ovs_header*,struct nlattr**) ; 
 struct sk_buff* ovs_vport_cmd_alloc_info () ; 
 int ovs_vport_cmd_fill_info (struct vport*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_get(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct sk_buff *reply;
	struct vport *vport;
	int err;

	reply = ovs_vport_cmd_alloc_info();
	if (!reply)
		return -ENOMEM;

	rcu_read_lock();
	vport = lookup_vport(sock_net(skb->sk), ovs_header, a);
	err = PTR_ERR(vport);
	if (IS_ERR(vport))
		goto exit_unlock_free;
	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_GET, GFP_ATOMIC);
	BUG_ON(err < 0);
	rcu_read_unlock();

	return genlmsg_reply(reply, info);

exit_unlock_free:
	rcu_read_unlock();
	kfree_skb(reply);
	return err;
}