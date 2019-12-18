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
 int /*<<< orphan*/  nf_ct_gre_keymap_flush (struct net*) ; 

void nf_conntrack_proto_pernet_fini(struct net *net)
{
#ifdef CONFIG_NF_CT_PROTO_GRE
	nf_ct_gre_keymap_flush(net);
#endif
}