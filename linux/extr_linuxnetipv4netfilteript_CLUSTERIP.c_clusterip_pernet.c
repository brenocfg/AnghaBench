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
struct clusterip_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clusterip_net_id ; 
 struct clusterip_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct clusterip_net *clusterip_pernet(struct net *net)
{
	return net_generic(net, clusterip_net_id);
}