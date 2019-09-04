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
typedef  int /*<<< orphan*/  u32 ;
struct socket {TYPE_1__* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  aa_sk_perm (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int af_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int in_interrupt () ; 
 int /*<<< orphan*/  opt_perm (char const*,int /*<<< orphan*/ ,struct socket*,int,int) ; 

__attribute__((used)) static int aa_sock_opt_perm(const char *op, u32 request, struct socket *sock,
			    int level, int optname)
{
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(in_interrupt());

	return af_select(sock->sk->sk_family,
			 opt_perm(op, request, sock, level, optname),
			 aa_sk_perm(op, request, sock->sk));
}