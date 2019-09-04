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
struct jffs2_sb_info {int /*<<< orphan*/  inocache_lock; int /*<<< orphan*/  inocache_wq; } ;
struct jffs2_inode_info {int dummy; } ;
struct jffs2_inode_cache {scalar_t__ state; int /*<<< orphan*/  ino; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct jffs2_inode_info* ERR_CAST (struct inode*) ; 
 struct jffs2_inode_info* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ INO_STATE_CHECKEDABSENT ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct inode*) ; 
 int /*<<< orphan*/  OFNI_BS_2SFFJ (struct jffs2_sb_info*) ; 
 struct inode* ilookup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,int,...) ; 
 struct jffs2_inode_cache* jffs2_get_ino_cache (struct jffs2_sb_info*,int) ; 
 struct inode* jffs2_iget (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int,int) ; 
 int /*<<< orphan*/  sleep_on_spinunlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct jffs2_inode_info *jffs2_gc_fetch_inode(struct jffs2_sb_info *c,
					      int inum, int unlinked)
{
	struct inode *inode;
	struct jffs2_inode_cache *ic;

	if (unlinked) {
		/* The inode has zero nlink but its nodes weren't yet marked
		   obsolete. This has to be because we're still waiting for
		   the final (close() and) iput() to happen.

		   There's a possibility that the final iput() could have
		   happened while we were contemplating. In order to ensure
		   that we don't cause a new read_inode() (which would fail)
		   for the inode in question, we use ilookup() in this case
		   instead of iget().

		   The nlink can't _become_ zero at this point because we're
		   holding the alloc_sem, and jffs2_do_unlink() would also
		   need that while decrementing nlink on any inode.
		*/
		inode = ilookup(OFNI_BS_2SFFJ(c), inum);
		if (!inode) {
			jffs2_dbg(1, "ilookup() failed for ino #%u; inode is probably deleted.\n",
				  inum);

			spin_lock(&c->inocache_lock);
			ic = jffs2_get_ino_cache(c, inum);
			if (!ic) {
				jffs2_dbg(1, "Inode cache for ino #%u is gone\n",
					  inum);
				spin_unlock(&c->inocache_lock);
				return NULL;
			}
			if (ic->state != INO_STATE_CHECKEDABSENT) {
				/* Wait for progress. Don't just loop */
				jffs2_dbg(1, "Waiting for ino #%u in state %d\n",
					  ic->ino, ic->state);
				sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			} else {
				spin_unlock(&c->inocache_lock);
			}

			return NULL;
		}
	} else {
		/* Inode has links to it still; they're not going away because
		   jffs2_do_unlink() would need the alloc_sem and we have it.
		   Just iget() it, and if read_inode() is necessary that's OK.
		*/
		inode = jffs2_iget(OFNI_BS_2SFFJ(c), inum);
		if (IS_ERR(inode))
			return ERR_CAST(inode);
	}
	if (is_bad_inode(inode)) {
		pr_notice("Eep. read_inode() failed for ino #%u. unlinked %d\n",
			  inum, unlinked);
		/* NB. This will happen again. We need to do something appropriate here. */
		iput(inode);
		return ERR_PTR(-EIO);
	}

	return JFFS2_INODE_INFO(inode);
}