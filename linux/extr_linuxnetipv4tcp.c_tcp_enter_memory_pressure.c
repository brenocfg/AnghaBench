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
 int /*<<< orphan*/  LINUX_MIB_TCPMEMORYPRESSURES ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpxchg (scalar_t__*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_memory_pressure ; 

void tcp_enter_memory_pressure(struct sock *sk)
{
	unsigned long val;

	if (tcp_memory_pressure)
		return;
	val = jiffies;

	if (!val)
		val--;
	if (!cmpxchg(&tcp_memory_pressure, 0, val))
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMEMORYPRESSURES);
}