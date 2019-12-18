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
struct nfsd_file {unsigned int nf_hashval; unsigned int nf_may; int /*<<< orphan*/ * nf_mark; scalar_t__ nf_flags; int /*<<< orphan*/  nf_ref; struct inode* nf_inode; struct net* nf_net; int /*<<< orphan*/  nf_cred; int /*<<< orphan*/ * nf_file; int /*<<< orphan*/  nf_lru; int /*<<< orphan*/  nf_node; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSD_FILE_BREAK_READ ; 
 int /*<<< orphan*/  NFSD_FILE_BREAK_WRITE ; 
 unsigned int NFSD_FILE_MAY_MASK ; 
 unsigned int NFSD_MAY_NOT_BREAK_LEASE ; 
 unsigned int NFSD_MAY_READ ; 
 unsigned int NFSD_MAY_WRITE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_current_cred () ; 
 struct nfsd_file* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_file_slab ; 
 int /*<<< orphan*/  trace_nfsd_file_alloc (struct nfsd_file*) ; 

__attribute__((used)) static struct nfsd_file *
nfsd_file_alloc(struct inode *inode, unsigned int may, unsigned int hashval,
		struct net *net)
{
	struct nfsd_file *nf;

	nf = kmem_cache_alloc(nfsd_file_slab, GFP_KERNEL);
	if (nf) {
		INIT_HLIST_NODE(&nf->nf_node);
		INIT_LIST_HEAD(&nf->nf_lru);
		nf->nf_file = NULL;
		nf->nf_cred = get_current_cred();
		nf->nf_net = net;
		nf->nf_flags = 0;
		nf->nf_inode = inode;
		nf->nf_hashval = hashval;
		atomic_set(&nf->nf_ref, 1);
		nf->nf_may = may & NFSD_FILE_MAY_MASK;
		if (may & NFSD_MAY_NOT_BREAK_LEASE) {
			if (may & NFSD_MAY_WRITE)
				__set_bit(NFSD_FILE_BREAK_WRITE, &nf->nf_flags);
			if (may & NFSD_MAY_READ)
				__set_bit(NFSD_FILE_BREAK_READ, &nf->nf_flags);
		}
		nf->nf_mark = NULL;
		trace_nfsd_file_alloc(nf);
	}
	return nf;
}