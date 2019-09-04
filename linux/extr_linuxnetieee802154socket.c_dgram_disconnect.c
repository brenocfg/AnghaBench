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
struct dgram_sock {scalar_t__ connected; } ;

/* Variables and functions */
 struct dgram_sock* dgram_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int dgram_disconnect(struct sock *sk, int flags)
{
	struct dgram_sock *ro = dgram_sk(sk);

	lock_sock(sk);
	ro->connected = 0;
	release_sock(sk);

	return 0;
}