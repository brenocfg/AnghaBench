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
typedef  scalar_t__ u32 ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ tipc_own_addr (struct net*) ; 

__attribute__((used)) static inline int in_own_node(struct net *net, u32 addr)
{
	return addr == tipc_own_addr(net) || !addr;
}