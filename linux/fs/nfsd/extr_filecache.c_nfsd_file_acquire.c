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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_dentry; } ;
struct nfsd_file {int /*<<< orphan*/  nf_flags; int /*<<< orphan*/  nf_file; scalar_t__ nf_mark; int /*<<< orphan*/  nf_node; int /*<<< orphan*/  nf_lru; int /*<<< orphan*/  nf_ref; int /*<<< orphan*/  nf_rcu; } ;
struct net {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  nfb_lock; int /*<<< orphan*/  nfb_count; int /*<<< orphan*/  nfb_maxcount; int /*<<< orphan*/  nfb_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_FILE_BREAK_READ ; 
 int /*<<< orphan*/  NFSD_FILE_BREAK_WRITE ; 
 int /*<<< orphan*/  NFSD_FILE_HASHED ; 
 int /*<<< orphan*/  NFSD_FILE_HASH_BITS ; 
 int /*<<< orphan*/  NFSD_FILE_PENDING ; 
 unsigned int NFSD_MAY_NOT_BREAK_LEASE ; 
 unsigned int NFSD_MAY_OWNER_OVERRIDE ; 
 unsigned int NFSD_MAY_WRITE ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ hash_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 struct nfsd_file* nfsd_file_alloc (struct inode*,unsigned int,unsigned int,struct net*) ; 
 int /*<<< orphan*/  nfsd_file_cache_hits ; 
 struct nfsd_file* nfsd_file_find_locked (struct inode*,unsigned int,unsigned int,struct net*) ; 
 TYPE_1__* nfsd_file_hashtbl ; 
 int /*<<< orphan*/  nfsd_file_lru ; 
 scalar_t__ nfsd_file_mark_find_or_create (struct nfsd_file*) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 int /*<<< orphan*/  nfsd_file_put_noref (struct nfsd_file*) ; 
 int /*<<< orphan*/  nfsd_file_slab_free (int /*<<< orphan*/ *) ; 
 int nfsd_file_unhash (struct nfsd_file*) ; 
 int /*<<< orphan*/  nfsd_filecache_count ; 
 int /*<<< orphan*/  nfsd_open_break_lease (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ nfsd_open_verified (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_jukebox ; 
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfsd_file_acquire (struct svc_rqst*,unsigned int,struct inode*,unsigned int,struct nfsd_file*,scalar_t__) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__be32
nfsd_file_acquire(struct svc_rqst *rqstp, struct svc_fh *fhp,
		  unsigned int may_flags, struct nfsd_file **pnf)
{
	__be32	status;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_file *nf, *new;
	struct inode *inode;
	unsigned int hashval;

	/* FIXME: skip this if fh_dentry is already set? */
	status = fh_verify(rqstp, fhp, S_IFREG,
				may_flags|NFSD_MAY_OWNER_OVERRIDE);
	if (status != nfs_ok)
		return status;

	inode = d_inode(fhp->fh_dentry);
	hashval = (unsigned int)hash_long(inode->i_ino, NFSD_FILE_HASH_BITS);
retry:
	rcu_read_lock();
	nf = nfsd_file_find_locked(inode, may_flags, hashval, net);
	rcu_read_unlock();
	if (nf)
		goto wait_for_construction;

	new = nfsd_file_alloc(inode, may_flags, hashval, net);
	if (!new) {
		trace_nfsd_file_acquire(rqstp, hashval, inode, may_flags,
					NULL, nfserr_jukebox);
		return nfserr_jukebox;
	}

	spin_lock(&nfsd_file_hashtbl[hashval].nfb_lock);
	nf = nfsd_file_find_locked(inode, may_flags, hashval, net);
	if (nf == NULL)
		goto open_file;
	spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
	nfsd_file_slab_free(&new->nf_rcu);

wait_for_construction:
	wait_on_bit(&nf->nf_flags, NFSD_FILE_PENDING, TASK_UNINTERRUPTIBLE);

	/* Did construction of this file fail? */
	if (!test_bit(NFSD_FILE_HASHED, &nf->nf_flags)) {
		nfsd_file_put_noref(nf);
		goto retry;
	}

	this_cpu_inc(nfsd_file_cache_hits);

	if (!(may_flags & NFSD_MAY_NOT_BREAK_LEASE)) {
		bool write = (may_flags & NFSD_MAY_WRITE);

		if (test_bit(NFSD_FILE_BREAK_READ, &nf->nf_flags) ||
		    (test_bit(NFSD_FILE_BREAK_WRITE, &nf->nf_flags) && write)) {
			status = nfserrno(nfsd_open_break_lease(
					file_inode(nf->nf_file), may_flags));
			if (status == nfs_ok) {
				clear_bit(NFSD_FILE_BREAK_READ, &nf->nf_flags);
				if (write)
					clear_bit(NFSD_FILE_BREAK_WRITE,
						  &nf->nf_flags);
			}
		}
	}
out:
	if (status == nfs_ok) {
		*pnf = nf;
	} else {
		nfsd_file_put(nf);
		nf = NULL;
	}

	trace_nfsd_file_acquire(rqstp, hashval, inode, may_flags, nf, status);
	return status;
open_file:
	nf = new;
	/* Take reference for the hashtable */
	atomic_inc(&nf->nf_ref);
	__set_bit(NFSD_FILE_HASHED, &nf->nf_flags);
	__set_bit(NFSD_FILE_PENDING, &nf->nf_flags);
	list_lru_add(&nfsd_file_lru, &nf->nf_lru);
	hlist_add_head_rcu(&nf->nf_node, &nfsd_file_hashtbl[hashval].nfb_head);
	++nfsd_file_hashtbl[hashval].nfb_count;
	nfsd_file_hashtbl[hashval].nfb_maxcount = max(nfsd_file_hashtbl[hashval].nfb_maxcount,
			nfsd_file_hashtbl[hashval].nfb_count);
	spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
	atomic_long_inc(&nfsd_filecache_count);

	nf->nf_mark = nfsd_file_mark_find_or_create(nf);
	if (nf->nf_mark)
		status = nfsd_open_verified(rqstp, fhp, S_IFREG,
				may_flags, &nf->nf_file);
	else
		status = nfserr_jukebox;
	/*
	 * If construction failed, or we raced with a call to unlink()
	 * then unhash.
	 */
	if (status != nfs_ok || inode->i_nlink == 0) {
		bool do_free;
		spin_lock(&nfsd_file_hashtbl[hashval].nfb_lock);
		do_free = nfsd_file_unhash(nf);
		spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
		if (do_free)
			nfsd_file_put_noref(nf);
	}
	clear_bit_unlock(NFSD_FILE_PENDING, &nf->nf_flags);
	smp_mb__after_atomic();
	wake_up_bit(&nf->nf_flags, NFSD_FILE_PENDING);
	goto out;
}