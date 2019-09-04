#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* sk; } ;
struct sctp_association {int sndbuf_used; TYPE_1__ base; TYPE_2__* ep; } ;
struct TYPE_7__ {int sk_sndbuf; int sk_userlocks; } ;
struct TYPE_6__ {scalar_t__ sndbuf_policy; } ;

/* Variables and functions */
 int SOCK_SNDBUF_LOCK ; 
 int sk_stream_wspace (TYPE_3__*) ; 
 int sk_wmem_alloc_get (TYPE_3__*) ; 

__attribute__((used)) static inline int sctp_wspace(struct sctp_association *asoc)
{
	int amt;

	if (asoc->ep->sndbuf_policy)
		amt = asoc->sndbuf_used;
	else
		amt = sk_wmem_alloc_get(asoc->base.sk);

	if (amt >= asoc->base.sk->sk_sndbuf) {
		if (asoc->base.sk->sk_userlocks & SOCK_SNDBUF_LOCK)
			amt = 0;
		else {
			amt = sk_stream_wspace(asoc->base.sk);
			if (amt < 0)
				amt = 0;
		}
	} else {
		amt = asoc->base.sk->sk_sndbuf - amt;
	}
	return amt;
}