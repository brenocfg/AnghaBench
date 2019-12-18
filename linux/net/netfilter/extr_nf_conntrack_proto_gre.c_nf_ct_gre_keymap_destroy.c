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
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
 int IP_CT_DIR_MAX ; 
 int IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  keymap_lock ; 
 int /*<<< orphan*/  kfree_rcu (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct nf_ct_pptp_master* nfct_help_data (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void nf_ct_gre_keymap_destroy(struct nf_conn *ct)
{
	struct nf_ct_pptp_master *ct_pptp_info = nfct_help_data(ct);
	enum ip_conntrack_dir dir;

	pr_debug("entering for ct %p\n", ct);

	spin_lock_bh(&keymap_lock);
	for (dir = IP_CT_DIR_ORIGINAL; dir < IP_CT_DIR_MAX; dir++) {
		if (ct_pptp_info->keymap[dir]) {
			pr_debug("removing %p from list\n",
				 ct_pptp_info->keymap[dir]);
			list_del_rcu(&ct_pptp_info->keymap[dir]->list);
			kfree_rcu(ct_pptp_info->keymap[dir], rcu);
			ct_pptp_info->keymap[dir] = NULL;
		}
	}
	spin_unlock_bh(&keymap_lock);
}