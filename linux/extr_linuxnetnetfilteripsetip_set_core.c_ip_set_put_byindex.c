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
struct net {int dummy; } ;
struct ip_set_net {int dummy; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_set_put_byindex (struct ip_set_net*,int /*<<< orphan*/ ) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 

void
ip_set_put_byindex(struct net *net, ip_set_id_t index)
{
	struct ip_set_net *inst = ip_set_pernet(net);

	__ip_set_put_byindex(inst, index);
}