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
struct tcp_congestion_ops {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_congestion_control; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CA_NAME_MAX ; 
 struct tcp_congestion_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tcp_get_default_congestion_control(struct net *net, char *name)
{
	const struct tcp_congestion_ops *ca;

	rcu_read_lock();
	ca = rcu_dereference(net->ipv4.tcp_congestion_control);
	strncpy(name, ca->name, TCP_CA_NAME_MAX);
	rcu_read_unlock();
}