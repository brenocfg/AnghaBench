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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfo_active_disable_stamp; int /*<<< orphan*/  tfo_active_disable_times; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPFASTOPENBLACKHOLE ; 
 int /*<<< orphan*/  NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct net* sock_net (struct sock*) ; 

void tcp_fastopen_active_disable(struct sock *sk)
{
	struct net *net = sock_net(sk);

	atomic_inc(&net->ipv4.tfo_active_disable_times);
	net->ipv4.tfo_active_disable_stamp = jiffies;
	NET_INC_STATS(net, LINUX_MIB_TCPFASTOPENBLACKHOLE);
}