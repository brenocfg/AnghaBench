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
struct sock {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * icsk_af_ops; } ;

/* Variables and functions */
 int dccp_init_sock (struct sock*,int) ; 
 int /*<<< orphan*/  dccp_ipv6_af_ops ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dccp_v6_init_sock(struct sock *sk)
{
	static __u8 dccp_v6_ctl_sock_initialized;
	int err = dccp_init_sock(sk, dccp_v6_ctl_sock_initialized);

	if (err == 0) {
		if (unlikely(!dccp_v6_ctl_sock_initialized))
			dccp_v6_ctl_sock_initialized = 1;
		inet_csk(sk)->icsk_af_ops = &dccp_ipv6_af_ops;
	}

	return err;
}