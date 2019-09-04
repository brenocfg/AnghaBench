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
struct sock {int /*<<< orphan*/  sk_callback_lock; scalar_t__ sk_socket; } ;
struct TYPE_2__ {unsigned long i_ino; } ;

/* Variables and functions */
 TYPE_1__* SOCK_INODE (scalar_t__) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

unsigned long sock_i_ino(struct sock *sk)
{
	unsigned long ino;

	read_lock_bh(&sk->sk_callback_lock);
	ino = sk->sk_socket ? SOCK_INODE(sk->sk_socket)->i_ino : 0;
	read_unlock_bh(&sk->sk_callback_lock);
	return ino;
}