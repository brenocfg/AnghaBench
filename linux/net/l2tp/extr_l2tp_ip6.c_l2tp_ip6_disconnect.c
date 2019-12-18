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

/* Variables and functions */
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int __udp_disconnect (struct sock*,int) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_ip6_disconnect(struct sock *sk, int flags)
{
	if (sock_flag(sk, SOCK_ZAPPED))
		return 0;

	return __udp_disconnect(sk, flags);
}