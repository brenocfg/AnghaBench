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
struct TYPE_2__ {int /*<<< orphan*/  bind_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __register_prot_hook (struct sock*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 TYPE_1__* pkt_sk (struct sock*) ; 

__attribute__((used)) static void register_prot_hook(struct sock *sk)
{
	lockdep_assert_held_once(&pkt_sk(sk)->bind_lock);
	__register_prot_hook(sk);
}