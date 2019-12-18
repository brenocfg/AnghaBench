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
struct nf_gre_net {int /*<<< orphan*/ * timeouts; int /*<<< orphan*/  keymap_list; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int GRE_CT_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nf_gre_net* gre_pernet (struct net*) ; 
 int /*<<< orphan*/ * gre_timeouts ; 

void nf_conntrack_gre_init_net(struct net *net)
{
	struct nf_gre_net *net_gre = gre_pernet(net);
	int i;

	INIT_LIST_HEAD(&net_gre->keymap_list);
	for (i = 0; i < GRE_CT_MAX; i++)
		net_gre->timeouts[i] = gre_timeouts[i];
}