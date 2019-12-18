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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  rsk_refcnt; } ;
struct inet_connection_sock {TYPE_1__* icsk_af_ops; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsoffset; } ;
struct TYPE_3__ {struct sock* (* syn_recv_sock ) (struct sock*,struct sk_buff*,struct request_sock*,struct dst_entry*,int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __reqsk_free (struct request_sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ inet_csk_reqsk_queue_add (struct sock*,struct request_sock*,struct sock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,struct sk_buff*) ; 
 struct sock* stub1 (struct sock*,struct sk_buff*,struct request_sock*,struct dst_entry*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

struct sock *tcp_get_cookie_sock(struct sock *sk, struct sk_buff *skb,
				 struct request_sock *req,
				 struct dst_entry *dst, u32 tsoff)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct sock *child;
	bool own_req;

	child = icsk->icsk_af_ops->syn_recv_sock(sk, skb, req, dst,
						 NULL, &own_req);
	if (child) {
		refcount_set(&req->rsk_refcnt, 1);
		tcp_sk(child)->tsoffset = tsoff;
		sock_rps_save_rxhash(child, skb);
		if (inet_csk_reqsk_queue_add(sk, req, child))
			return child;

		bh_unlock_sock(child);
		sock_put(child);
	}
	__reqsk_free(req);

	return NULL;
}