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
struct sock {int dummy; } ;
struct nr_sock {scalar_t__ t4; int /*<<< orphan*/  t4timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 

void nr_start_t4timer(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);

	sk_reset_timer(sk, &nr->t4timer, jiffies + nr->t4);
}