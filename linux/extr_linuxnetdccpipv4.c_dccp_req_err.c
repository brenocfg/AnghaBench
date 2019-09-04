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
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;
struct request_sock {int /*<<< orphan*/  rsk_listener; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dreq_gss; int /*<<< orphan*/  dreq_iss; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_OUTOFWINDOWICMPS ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  between48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (int /*<<< orphan*/ ,struct request_sock*) ; 
 struct request_sock* inet_reqsk (struct sock*) ; 
 int /*<<< orphan*/  reqsk_put (struct request_sock*) ; 
 struct net* sock_net (struct sock*) ; 

void dccp_req_err(struct sock *sk, u64 seq)
	{
	struct request_sock *req = inet_reqsk(sk);
	struct net *net = sock_net(sk);

	/*
	 * ICMPs are not backlogged, hence we cannot get an established
	 * socket here.
	 */
	if (!between48(seq, dccp_rsk(req)->dreq_iss, dccp_rsk(req)->dreq_gss)) {
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
	} else {
		/*
		 * Still in RESPOND, just remove it silently.
		 * There is no good way to pass the error to the newly
		 * created socket, and POSIX does not want network
		 * errors returned from accept().
		 */
		inet_csk_reqsk_queue_drop(req->rsk_listener, req);
	}
	reqsk_put(req);
}