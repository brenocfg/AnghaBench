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
struct sock {int sk_sndbuf; } ;

/* Variables and functions */
 int sk_wmem_alloc_get (struct sock*) ; 

__attribute__((used)) static int sctp_writeable(struct sock *sk)
{
	int amt = 0;

	amt = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
	if (amt < 0)
		amt = 0;
	return amt;
}