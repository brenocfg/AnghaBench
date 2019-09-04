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
struct nf_ct_pptp_master {struct nf_conn** keymap; } ;
struct nf_conn {int /*<<< orphan*/  list; } ;
struct netns_proto_gre {int /*<<< orphan*/  keymap_lock; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
 int IP_CT_DIR_MAX ; 
 int IP_CT_DIR_ORIGINAL ; 
 struct netns_proto_gre* gre_pernet (struct net*) ; 
 int /*<<< orphan*/  kfree (struct nf_conn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 struct nf_ct_pptp_master* nfct_help_data (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void nf_ct_gre_keymap_destroy(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);
	struct netns_proto_gre *net_gre = gre_pernet(net);
	struct nf_ct_pptp_master *ct_pptp_info = nfct_help_data(ct);
	enum ip_conntrack_dir dir;

	pr_debug("entering for ct %p\n", ct);

	write_lock_bh(&net_gre->keymap_lock);
	for (dir = IP_CT_DIR_ORIGINAL; dir < IP_CT_DIR_MAX; dir++) {
		if (ct_pptp_info->keymap[dir]) {
			pr_debug("removing %p from list\n",
				 ct_pptp_info->keymap[dir]);
			list_del(&ct_pptp_info->keymap[dir]->list);
			kfree(ct_pptp_info->keymap[dir]);
			ct_pptp_info->keymap[dir] = NULL;
		}
	}
	write_unlock_bh(&net_gre->keymap_lock);
}