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
struct datapath {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 

__attribute__((used)) static inline void ovs_dp_set_net(struct datapath *dp, struct net *net)
{
	write_pnet(&dp->net, net);
}