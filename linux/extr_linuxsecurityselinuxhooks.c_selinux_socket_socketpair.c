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
struct socket {TYPE_1__* sk; } ;
struct sk_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  peer_sid; } ;
struct TYPE_2__ {struct sk_security_struct* sk_security; } ;

/* Variables and functions */

__attribute__((used)) static int selinux_socket_socketpair(struct socket *socka,
				     struct socket *sockb)
{
	struct sk_security_struct *sksec_a = socka->sk->sk_security;
	struct sk_security_struct *sksec_b = sockb->sk->sk_security;

	sksec_a->peer_sid = sksec_b->sid;
	sksec_b->peer_sid = sksec_a->sid;

	return 0;
}