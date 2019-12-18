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
struct unix_diag_req {int udiag_show; } ;
struct unix_diag_msg {int udiag_ino; int /*<<< orphan*/  udiag_cookie; scalar_t__ pad; int /*<<< orphan*/  udiag_state; int /*<<< orphan*/  udiag_type; int /*<<< orphan*/  udiag_family; } ;
struct sock {int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_type; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 int UDIAG_SHOW_ICONS ; 
 int UDIAG_SHOW_MEMINFO ; 
 int UDIAG_SHOW_NAME ; 
 int UDIAG_SHOW_PEER ; 
 int UDIAG_SHOW_RQLEN ; 
 int UDIAG_SHOW_UID ; 
 int UDIAG_SHOW_VFS ; 
 int /*<<< orphan*/  UNIX_DIAG_MEMINFO ; 
 int /*<<< orphan*/  UNIX_DIAG_SHUTDOWN ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct unix_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_diag_dump_icons (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_dump_name (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_dump_peer (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_dump_uid (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_dump_vfs (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_show_rqlen (struct sock*,struct sk_buff*) ; 
 scalar_t__ sock_diag_put_meminfo (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_diag_save_cookie (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb, struct unix_diag_req *req,
		u32 portid, u32 seq, u32 flags, int sk_ino)
{
	struct nlmsghdr *nlh;
	struct unix_diag_msg *rep;

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, sizeof(*rep),
			flags);
	if (!nlh)
		return -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->udiag_family = AF_UNIX;
	rep->udiag_type = sk->sk_type;
	rep->udiag_state = sk->sk_state;
	rep->pad = 0;
	rep->udiag_ino = sk_ino;
	sock_diag_save_cookie(sk, rep->udiag_cookie);

	if ((req->udiag_show & UDIAG_SHOW_NAME) &&
	    sk_diag_dump_name(sk, skb))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_VFS) &&
	    sk_diag_dump_vfs(sk, skb))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_PEER) &&
	    sk_diag_dump_peer(sk, skb))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_ICONS) &&
	    sk_diag_dump_icons(sk, skb))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_RQLEN) &&
	    sk_diag_show_rqlen(sk, skb))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, UNIX_DIAG_MEMINFO))
		goto out_nlmsg_trim;

	if (nla_put_u8(skb, UNIX_DIAG_SHUTDOWN, sk->sk_shutdown))
		goto out_nlmsg_trim;

	if ((req->udiag_show & UDIAG_SHOW_UID) &&
	    sk_diag_dump_uid(sk, skb))
		goto out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	return 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}