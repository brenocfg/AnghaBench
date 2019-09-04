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
struct sock {int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 

__attribute__((used)) static void rfcomm_l2state_change(struct sock *sk)
{
	BT_DBG("%p state %d", sk, sk->sk_state);
	rfcomm_schedule();
}