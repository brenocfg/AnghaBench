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
struct l2tp_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  l2tp_net_id ; 
 struct l2tp_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct l2tp_net *l2tp_pernet(const struct net *net)
{
	BUG_ON(!net);

	return net_generic(net, l2tp_net_id);
}