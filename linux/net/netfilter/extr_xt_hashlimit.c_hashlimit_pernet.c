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
struct hashlimit_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashlimit_net_id ; 
 struct hashlimit_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hashlimit_net *hashlimit_pernet(struct net *net)
{
	return net_generic(net, hashlimit_net_id);
}