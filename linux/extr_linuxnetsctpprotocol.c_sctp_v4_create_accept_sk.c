#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_5__* sk_prot; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; } ;
struct TYPE_8__ {TYPE_2__ v4; } ;
struct TYPE_9__ {TYPE_3__ primary_addr; } ;
struct sctp_association {TYPE_4__ peer; } ;
struct inet_sock {int /*<<< orphan*/  inet_daddr; } ;
struct TYPE_10__ {scalar_t__ (* init ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_copy_sock (struct sock*,struct sock*,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_v4_copy_ip_options (struct sock*,struct sock*) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct sock*) ; 

__attribute__((used)) static struct sock *sctp_v4_create_accept_sk(struct sock *sk,
					     struct sctp_association *asoc,
					     bool kern)
{
	struct sock *newsk = sk_alloc(sock_net(sk), PF_INET, GFP_KERNEL,
			sk->sk_prot, kern);
	struct inet_sock *newinet;

	if (!newsk)
		goto out;

	sock_init_data(NULL, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_reset_flag(newsk, SOCK_ZAPPED);

	sctp_v4_copy_ip_options(sk, newsk);

	newinet = inet_sk(newsk);

	newinet->inet_daddr = asoc->peer.primary_addr.v4.sin_addr.s_addr;

	sk_refcnt_debug_inc(newsk);

	if (newsk->sk_prot->init(newsk)) {
		sk_common_release(newsk);
		newsk = NULL;
	}

out:
	return newsk;
}