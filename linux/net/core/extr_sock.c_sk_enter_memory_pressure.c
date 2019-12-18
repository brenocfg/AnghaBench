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
struct sock {TYPE_1__* sk_prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter_memory_pressure ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void sk_enter_memory_pressure(struct sock *sk)
{
	if (!sk->sk_prot->enter_memory_pressure)
		return;

	sk->sk_prot->enter_memory_pressure(sk);
}