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
struct sock {int sk_sndbuf; } ;
struct TYPE_3__ {struct sock* sk; } ;
struct sctp_association {int sndbuf_used; TYPE_2__* ep; TYPE_1__ base; } ;
struct TYPE_4__ {scalar_t__ sndbuf_policy; } ;

/* Variables and functions */
 int sk_stream_wspace (struct sock*) ; 

__attribute__((used)) static inline int sctp_wspace(struct sctp_association *asoc)
{
	struct sock *sk = asoc->base.sk;

	return asoc->ep->sndbuf_policy ? sk->sk_sndbuf - asoc->sndbuf_used
				       : sk_stream_wspace(sk);
}