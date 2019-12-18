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
struct sock {scalar_t__ sk_sndbuf; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_3__ {scalar_t__ max_sdu; } ;
struct TYPE_4__ {TYPE_1__ txtp; } ;
struct atm_vcc {TYPE_2__ qos; } ;

/* Variables and functions */
 struct atm_vcc* atm_sk (struct sock*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int vcc_writable(struct sock *sk)
{
	struct atm_vcc *vcc = atm_sk(sk);

	return (vcc->qos.txtp.max_sdu +
		refcount_read(&sk->sk_wmem_alloc)) <= sk->sk_sndbuf;
}