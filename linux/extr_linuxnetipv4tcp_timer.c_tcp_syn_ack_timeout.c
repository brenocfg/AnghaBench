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
struct request_sock {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ireq_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPTIMEOUTS ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_rsk (struct request_sock const*) ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 

void tcp_syn_ack_timeout(const struct request_sock *req)
{
	struct net *net = read_pnet(&inet_rsk(req)->ireq_net);

	__NET_INC_STATS(net, LINUX_MIB_TCPTIMEOUTS);
}