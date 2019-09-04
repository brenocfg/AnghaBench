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
struct nf_ct_timeout {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_iterate_cleanup_net (struct net*,int /*<<< orphan*/ ,struct nf_ct_timeout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untimeout ; 

void nf_ct_untimeout(struct net *net, struct nf_ct_timeout *timeout)
{
	nf_ct_iterate_cleanup_net(net, untimeout, timeout, 0, 0);
}