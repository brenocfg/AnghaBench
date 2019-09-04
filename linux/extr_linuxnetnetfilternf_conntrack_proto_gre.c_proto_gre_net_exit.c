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

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_l4proto_gre4 ; 
 int /*<<< orphan*/  nf_ct_gre_keymap_flush (struct net*) ; 
 int /*<<< orphan*/  nf_ct_l4proto_pernet_unregister_one (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void proto_gre_net_exit(struct net *net)
{
	nf_ct_l4proto_pernet_unregister_one(net, &nf_conntrack_l4proto_gre4);
	nf_ct_gre_keymap_flush(net);
}