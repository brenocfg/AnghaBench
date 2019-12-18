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
struct j1939_sock {int /*<<< orphan*/  skb_pending; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct j1939_sock* j1939_sk (struct sock*) ; 

__attribute__((used)) static int j1939_sock_pending_get(struct sock *sk)
{
	struct j1939_sock *jsk = j1939_sk(sk);

	return atomic_read(&jsk->skb_pending);
}