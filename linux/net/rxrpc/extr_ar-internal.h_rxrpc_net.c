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
struct rxrpc_net {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct rxrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_net_id ; 

__attribute__((used)) static inline struct rxrpc_net *rxrpc_net(struct net *net)
{
	return net_generic(net, rxrpc_net_id);
}