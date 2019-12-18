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
struct nf_conn {struct nf_conn* master; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_gre_keymap_destroy (struct nf_conn*) ; 

__attribute__((used)) static void destroy_gre_conntrack(struct nf_conn *ct)
{
#ifdef CONFIG_NF_CT_PROTO_GRE
	struct nf_conn *master = ct->master;

	if (master)
		nf_ct_gre_keymap_destroy(master);
#endif
}