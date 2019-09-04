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
struct sock {int dummy; } ;
struct net {int dummy; } ;
struct audit_net {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_net_id ; 
 struct audit_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock *audit_get_sk(const struct net *net)
{
	struct audit_net *aunet;

	if (!net)
		return NULL;

	aunet = net_generic(net, audit_net_id);
	return aunet->sk;
}