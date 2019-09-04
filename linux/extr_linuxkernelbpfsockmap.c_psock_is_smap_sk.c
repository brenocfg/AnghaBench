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
struct TYPE_2__ {int /*<<< orphan*/ * icsk_ulp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_tcp_ulp_ops ; 
 TYPE_1__* inet_csk (struct sock*) ; 

__attribute__((used)) static bool psock_is_smap_sk(struct sock *sk)
{
	return inet_csk(sk)->icsk_ulp_ops == &bpf_tcp_ulp_ops;
}