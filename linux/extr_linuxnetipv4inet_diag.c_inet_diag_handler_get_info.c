#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_type; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  idiag_sport; } ;
struct inet_diag_msg {int /*<<< orphan*/  idiag_state; TYPE_1__ id; } ;
struct inet_diag_handler {int /*<<< orphan*/  (* idiag_get_info ) (struct sock*,struct inet_diag_msg*,void*) ;scalar_t__ idiag_info_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  inet_sport; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INET_DIAG_INFO ; 
 int /*<<< orphan*/  INET_DIAG_PAD ; 
 int /*<<< orphan*/  INET_DIAG_PROTOCOL ; 
 scalar_t__ IS_ERR (struct inet_diag_handler const*) ; 
 int PTR_ERR (struct inet_diag_handler const*) ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 scalar_t__ SOCK_STREAM ; 
 struct inet_diag_handler* inet_diag_lock_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_diag_msg_common_fill (struct inet_diag_msg*,struct sock*) ; 
 int /*<<< orphan*/  inet_diag_unlock_handler (struct inet_diag_handler const*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memset (struct inet_diag_msg*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve_64bit (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct inet_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct inet_diag_msg*,void*) ; 

__attribute__((used)) static
int inet_diag_handler_get_info(struct sk_buff *skb, struct sock *sk)
{
	const struct inet_diag_handler *handler;
	struct nlmsghdr *nlh;
	struct nlattr *attr;
	struct inet_diag_msg *r;
	void *info = NULL;
	int err = 0;

	nlh = nlmsg_put(skb, 0, 0, SOCK_DIAG_BY_FAMILY, sizeof(*r), 0);
	if (!nlh)
		return -ENOMEM;

	r = nlmsg_data(nlh);
	memset(r, 0, sizeof(*r));
	inet_diag_msg_common_fill(r, sk);
	if (sk->sk_type == SOCK_DGRAM || sk->sk_type == SOCK_STREAM)
		r->id.idiag_sport = inet_sk(sk)->inet_sport;
	r->idiag_state = sk->sk_state;

	if ((err = nla_put_u8(skb, INET_DIAG_PROTOCOL, sk->sk_protocol))) {
		nlmsg_cancel(skb, nlh);
		return err;
	}

	handler = inet_diag_lock_handler(sk->sk_protocol);
	if (IS_ERR(handler)) {
		inet_diag_unlock_handler(handler);
		nlmsg_cancel(skb, nlh);
		return PTR_ERR(handler);
	}

	attr = handler->idiag_info_size
		? nla_reserve_64bit(skb, INET_DIAG_INFO,
				    handler->idiag_info_size,
				    INET_DIAG_PAD)
		: NULL;
	if (attr)
		info = nla_data(attr);

	handler->idiag_get_info(sk, r, info);
	inet_diag_unlock_handler(handler);

	nlmsg_end(skb, nlh);
	return 0;
}