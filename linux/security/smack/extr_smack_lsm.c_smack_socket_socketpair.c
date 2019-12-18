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
struct socket_smack {int /*<<< orphan*/  smk_out; int /*<<< orphan*/  smk_packet; } ;
struct socket {TYPE_1__* sk; } ;
struct TYPE_2__ {struct socket_smack* sk_security; } ;

/* Variables and functions */

__attribute__((used)) static int smack_socket_socketpair(struct socket *socka,
		                   struct socket *sockb)
{
	struct socket_smack *asp = socka->sk->sk_security;
	struct socket_smack *bsp = sockb->sk->sk_security;

	asp->smk_packet = bsp->smk_out;
	bsp->smk_packet = asp->smk_out;

	return 0;
}