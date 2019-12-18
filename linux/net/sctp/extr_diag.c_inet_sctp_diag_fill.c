#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct user_namespace {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
struct sock {int sk_rcvbuf; int sk_sndbuf; int sk_forward_alloc; int sk_wmem_queued; int /*<<< orphan*/  sk_drops; TYPE_2__ sk_backlog; int /*<<< orphan*/  sk_omem_alloc; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct sctp_infox {struct sctp_association* asoc; struct sctp_info* sctpinfo; } ;
struct sctp_info {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_12__ {struct list_head address_list; } ;
struct TYPE_13__ {TYPE_5__ bind_addr; } ;
struct sctp_endpoint {TYPE_6__ base; } ;
struct TYPE_10__ {struct list_head address_list; } ;
struct TYPE_11__ {TYPE_3__ bind_addr; } ;
struct sctp_association {int sndbuf_used; TYPE_4__ base; int /*<<< orphan*/  rmem_alloc; TYPE_1__* ep; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct inet_diag_req_v2 {int idiag_ext; } ;
struct inet_diag_msg {scalar_t__ idiag_retrans; scalar_t__ idiag_timer; int /*<<< orphan*/  idiag_state; } ;
typedef  int /*<<< orphan*/  mem ;
struct TYPE_14__ {struct sctp_endpoint* ep; } ;
struct TYPE_8__ {scalar_t__ rcvbuf_policy; scalar_t__ sndbuf_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EMSGSIZE ; 
 int INET_DIAG_CONG ; 
 int INET_DIAG_INFO ; 
 int /*<<< orphan*/  INET_DIAG_PAD ; 
 int INET_DIAG_SKMEMINFO ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t SK_MEMINFO_BACKLOG ; 
 size_t SK_MEMINFO_DROPS ; 
 size_t SK_MEMINFO_FWD_ALLOC ; 
 size_t SK_MEMINFO_OPTMEM ; 
 size_t SK_MEMINFO_RCVBUF ; 
 size_t SK_MEMINFO_RMEM_ALLOC ; 
 size_t SK_MEMINFO_SNDBUF ; 
 int SK_MEMINFO_VARS ; 
 size_t SK_MEMINFO_WMEM_ALLOC ; 
 size_t SK_MEMINFO_WMEM_QUEUED ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ inet_diag_msg_attrs_fill (struct sock*,struct sk_buff*,struct inet_diag_msg*,int,struct user_namespace*,int) ; 
 int /*<<< orphan*/  inet_diag_msg_common_fill (struct inet_diag_msg*,struct sock*) ; 
 scalar_t__ inet_diag_msg_sctpaddrs_fill (struct sk_buff*,struct sctp_association*) ; 
 int /*<<< orphan*/  inet_diag_msg_sctpasoc_fill (struct inet_diag_msg*,struct sock*,struct sctp_association*) ; 
 scalar_t__ inet_diag_msg_sctpladdrs_fill (struct sk_buff*,struct list_head*) ; 
 void* nla_data (struct nlattr*) ; 
 scalar_t__ nla_put (struct sk_buff*,int,int,int**) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int,char*) ; 
 struct nlattr* nla_reserve_64bit (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct inet_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_diag_get_info (struct sock*,struct inet_diag_msg*,struct sctp_infox*) ; 
 TYPE_7__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 int sk_rmem_alloc_get (struct sock*) ; 
 int sk_wmem_alloc_get (struct sock*) ; 

__attribute__((used)) static int inet_sctp_diag_fill(struct sock *sk, struct sctp_association *asoc,
			       struct sk_buff *skb,
			       const struct inet_diag_req_v2 *req,
			       struct user_namespace *user_ns,
			       int portid, u32 seq, u16 nlmsg_flags,
			       const struct nlmsghdr *unlh,
			       bool net_admin)
{
	struct sctp_endpoint *ep = sctp_sk(sk)->ep;
	struct list_head *addr_list;
	struct inet_diag_msg *r;
	struct nlmsghdr  *nlh;
	int ext = req->idiag_ext;
	struct sctp_infox infox;
	void *info = NULL;

	nlh = nlmsg_put(skb, portid, seq, unlh->nlmsg_type, sizeof(*r),
			nlmsg_flags);
	if (!nlh)
		return -EMSGSIZE;

	r = nlmsg_data(nlh);
	BUG_ON(!sk_fullsock(sk));

	if (asoc) {
		inet_diag_msg_sctpasoc_fill(r, sk, asoc);
	} else {
		inet_diag_msg_common_fill(r, sk);
		r->idiag_state = sk->sk_state;
		r->idiag_timer = 0;
		r->idiag_retrans = 0;
	}

	if (inet_diag_msg_attrs_fill(sk, skb, r, ext, user_ns, net_admin))
		goto errout;

	if (ext & (1 << (INET_DIAG_SKMEMINFO - 1))) {
		u32 mem[SK_MEMINFO_VARS];
		int amt;

		if (asoc && asoc->ep->sndbuf_policy)
			amt = asoc->sndbuf_used;
		else
			amt = sk_wmem_alloc_get(sk);
		mem[SK_MEMINFO_WMEM_ALLOC] = amt;
		if (asoc && asoc->ep->rcvbuf_policy)
			amt = atomic_read(&asoc->rmem_alloc);
		else
			amt = sk_rmem_alloc_get(sk);
		mem[SK_MEMINFO_RMEM_ALLOC] = amt;
		mem[SK_MEMINFO_RCVBUF] = sk->sk_rcvbuf;
		mem[SK_MEMINFO_SNDBUF] = sk->sk_sndbuf;
		mem[SK_MEMINFO_FWD_ALLOC] = sk->sk_forward_alloc;
		mem[SK_MEMINFO_WMEM_QUEUED] = sk->sk_wmem_queued;
		mem[SK_MEMINFO_OPTMEM] = atomic_read(&sk->sk_omem_alloc);
		mem[SK_MEMINFO_BACKLOG] = READ_ONCE(sk->sk_backlog.len);
		mem[SK_MEMINFO_DROPS] = atomic_read(&sk->sk_drops);

		if (nla_put(skb, INET_DIAG_SKMEMINFO, sizeof(mem), &mem) < 0)
			goto errout;
	}

	if (ext & (1 << (INET_DIAG_INFO - 1))) {
		struct nlattr *attr;

		attr = nla_reserve_64bit(skb, INET_DIAG_INFO,
					 sizeof(struct sctp_info),
					 INET_DIAG_PAD);
		if (!attr)
			goto errout;

		info = nla_data(attr);
	}
	infox.sctpinfo = (struct sctp_info *)info;
	infox.asoc = asoc;
	sctp_diag_get_info(sk, r, &infox);

	addr_list = asoc ? &asoc->base.bind_addr.address_list
			 : &ep->base.bind_addr.address_list;
	if (inet_diag_msg_sctpladdrs_fill(skb, addr_list))
		goto errout;

	if (asoc && (ext & (1 << (INET_DIAG_CONG - 1))))
		if (nla_put_string(skb, INET_DIAG_CONG, "reno") < 0)
			goto errout;

	if (asoc && inet_diag_msg_sctpaddrs_fill(skb, asoc))
		goto errout;

	nlmsg_end(skb, nlh);
	return 0;

errout:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}