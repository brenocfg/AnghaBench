#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsd_file {size_t nf_hashval; int /*<<< orphan*/  nf_lru; int /*<<< orphan*/  nf_node; int /*<<< orphan*/  nf_net; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfb_count; int /*<<< orphan*/  nfb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd_file_check_write_error (struct nfsd_file*) ; 
 TYPE_1__* nfsd_file_hashtbl ; 
 int /*<<< orphan*/  nfsd_file_lru ; 
 int /*<<< orphan*/  nfsd_filecache_count ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_reset_boot_verifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfsd_file_unhash (struct nfsd_file*) ; 

__attribute__((used)) static void
nfsd_file_do_unhash(struct nfsd_file *nf)
{
	lockdep_assert_held(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);

	trace_nfsd_file_unhash(nf);

	if (nfsd_file_check_write_error(nf))
		nfsd_reset_boot_verifier(net_generic(nf->nf_net, nfsd_net_id));
	--nfsd_file_hashtbl[nf->nf_hashval].nfb_count;
	hlist_del_rcu(&nf->nf_node);
	if (!list_empty(&nf->nf_lru))
		list_lru_del(&nfsd_file_lru, &nf->nf_lru);
	atomic_long_dec(&nfsd_filecache_count);
}