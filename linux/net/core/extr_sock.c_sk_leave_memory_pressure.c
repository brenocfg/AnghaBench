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
struct TYPE_2__ {unsigned long* memory_pressure; int /*<<< orphan*/  (* leave_memory_pressure ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ READ_ONCE (unsigned long) ; 
 int /*<<< orphan*/  WRITE_ONCE (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void sk_leave_memory_pressure(struct sock *sk)
{
	if (sk->sk_prot->leave_memory_pressure) {
		sk->sk_prot->leave_memory_pressure(sk);
	} else {
		unsigned long *memory_pressure = sk->sk_prot->memory_pressure;

		if (memory_pressure && READ_ONCE(*memory_pressure))
			WRITE_ONCE(*memory_pressure, 0);
	}
}