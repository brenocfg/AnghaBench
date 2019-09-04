#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct super_block {int dummy; } ;
struct metapage {int dummy; } ;
struct ldtentry {int /*<<< orphan*/  inumber; } ;
struct inode {struct super_block* i_sb; } ;
struct component_name {int /*<<< orphan*/  name; int /*<<< orphan*/  namlen; } ;
struct btstack {int nsplit; struct btframe* top; } ;
struct btframe {int index; struct metapage* mp; void* bn; } ;
typedef  size_t s8 ;
typedef  void* s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
typedef  scalar_t__ ino_t ;
struct TYPE_8__ {int nextindex; int flag; } ;
struct TYPE_9__ {int /*<<< orphan*/ * slot; TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;
struct TYPE_10__ {int mntflag; int l2bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLR (struct btstack*) ; 
 int BT_LEAF ; 
 int /*<<< orphan*/  BT_PUSH (struct btstack*,void*,int) ; 
 int /*<<< orphan*/  BT_STACK_DUMP (struct btstack*) ; 
 scalar_t__ BT_STACK_FULL (struct btstack*) ; 
 int /*<<< orphan*/  DT_GETPAGE (struct inode*,void*,struct metapage*,int,TYPE_2__*,int) ; 
 size_t* DT_GETSTBL (TYPE_2__*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int EEXIST ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ESTALE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int JFS_CREATE ; 
 int JFS_LOOKUP ; 
 scalar_t__ JFS_NAME_MAX ; 
 int JFS_OS2 ; 
 int JFS_REMOVE ; 
 int JFS_RENAME ; 
 TYPE_5__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  UniStrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* addressPXD (int /*<<< orphan*/ *) ; 
 int ciCompare (struct component_name*,TYPE_2__*,size_t,int) ; 
 int /*<<< orphan*/  ciToUpper (struct component_name*) ; 
 int dtCompare (struct component_name*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  jfs_error (struct super_block*,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lengthPXD (int /*<<< orphan*/ *) ; 

int dtSearch(struct inode *ip, struct component_name * key, ino_t * data,
	     struct btstack * btstack, int flag)
{
	int rc = 0;
	int cmp = 1;		/* init for empty page */
	s64 bn;
	struct metapage *mp;
	dtpage_t *p;
	s8 *stbl;
	int base, index, lim;
	struct btframe *btsp;
	pxd_t *pxd;
	int psize = 288;	/* initial in-line directory */
	ino_t inumber;
	struct component_name ciKey;
	struct super_block *sb = ip->i_sb;

	ciKey.name = kmalloc_array(JFS_NAME_MAX + 1, sizeof(wchar_t),
				   GFP_NOFS);
	if (!ciKey.name) {
		rc = -ENOMEM;
		goto dtSearch_Exit2;
	}


	/* uppercase search key for c-i directory */
	UniStrcpy(ciKey.name, key->name);
	ciKey.namlen = key->namlen;

	/* only uppercase if case-insensitive support is on */
	if ((JFS_SBI(sb)->mntflag & JFS_OS2) == JFS_OS2) {
		ciToUpper(&ciKey);
	}
	BT_CLR(btstack);	/* reset stack */

	/* init level count for max pages to split */
	btstack->nsplit = 1;

	/*
	 *	search down tree from root:
	 *
	 * between two consecutive entries of <Ki, Pi> and <Kj, Pj> of
	 * internal page, child page Pi contains entry with k, Ki <= K < Kj.
	 *
	 * if entry with search key K is not found
	 * internal page search find the entry with largest key Ki
	 * less than K which point to the child page to search;
	 * leaf page search find the entry with smallest key Kj
	 * greater than K so that the returned index is the position of
	 * the entry to be shifted right for insertion of new entry.
	 * for empty tree, search key is greater than any key of the tree.
	 *
	 * by convention, root bn = 0.
	 */
	for (bn = 0;;) {
		/* get/pin the page to search */
		DT_GETPAGE(ip, bn, mp, psize, p, rc);
		if (rc)
			goto dtSearch_Exit1;

		/* get sorted entry table of the page */
		stbl = DT_GETSTBL(p);

		/*
		 * binary search with search key K on the current page.
		 */
		for (base = 0, lim = p->header.nextindex; lim; lim >>= 1) {
			index = base + (lim >> 1);

			if (p->header.flag & BT_LEAF) {
				/* uppercase leaf name to compare */
				cmp =
				    ciCompare(&ciKey, p, stbl[index],
					      JFS_SBI(sb)->mntflag);
			} else {
				/* router key is in uppercase */

				cmp = dtCompare(&ciKey, p, stbl[index]);


			}
			if (cmp == 0) {
				/*
				 *	search hit
				 */
				/* search hit - leaf page:
				 * return the entry found
				 */
				if (p->header.flag & BT_LEAF) {
					inumber = le32_to_cpu(
			((struct ldtentry *) & p->slot[stbl[index]])->inumber);

					/*
					 * search for JFS_LOOKUP
					 */
					if (flag == JFS_LOOKUP) {
						*data = inumber;
						rc = 0;
						goto out;
					}

					/*
					 * search for JFS_CREATE
					 */
					if (flag == JFS_CREATE) {
						*data = inumber;
						rc = -EEXIST;
						goto out;
					}

					/*
					 * search for JFS_REMOVE or JFS_RENAME
					 */
					if ((flag == JFS_REMOVE ||
					     flag == JFS_RENAME) &&
					    *data != inumber) {
						rc = -ESTALE;
						goto out;
					}

					/*
					 * JFS_REMOVE|JFS_FINDDIR|JFS_RENAME
					 */
					/* save search result */
					*data = inumber;
					btsp = btstack->top;
					btsp->bn = bn;
					btsp->index = index;
					btsp->mp = mp;

					rc = 0;
					goto dtSearch_Exit1;
				}

				/* search hit - internal page:
				 * descend/search its child page
				 */
				goto getChild;
			}

			if (cmp > 0) {
				base = index + 1;
				--lim;
			}
		}

		/*
		 *	search miss
		 *
		 * base is the smallest index with key (Kj) greater than
		 * search key (K) and may be zero or (maxindex + 1) index.
		 */
		/*
		 * search miss - leaf page
		 *
		 * return location of entry (base) where new entry with
		 * search key K is to be inserted.
		 */
		if (p->header.flag & BT_LEAF) {
			/*
			 * search for JFS_LOOKUP, JFS_REMOVE, or JFS_RENAME
			 */
			if (flag == JFS_LOOKUP || flag == JFS_REMOVE ||
			    flag == JFS_RENAME) {
				rc = -ENOENT;
				goto out;
			}

			/*
			 * search for JFS_CREATE|JFS_FINDDIR:
			 *
			 * save search result
			 */
			*data = 0;
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = base;
			btsp->mp = mp;

			rc = 0;
			goto dtSearch_Exit1;
		}

		/*
		 * search miss - internal page
		 *
		 * if base is non-zero, decrement base by one to get the parent
		 * entry of the child page to search.
		 */
		index = base ? base - 1 : base;

		/*
		 * go down to child page
		 */
	      getChild:
		/* update max. number of pages to split */
		if (BT_STACK_FULL(btstack)) {
			/* Something's corrupted, mark filesystem dirty so
			 * chkdsk will fix it.
			 */
			jfs_error(sb, "stack overrun!\n");
			BT_STACK_DUMP(btstack);
			rc = -EIO;
			goto out;
		}
		btstack->nsplit++;

		/* push (bn, index) of the parent page/entry */
		BT_PUSH(btstack, bn, index);

		/* get the child page block number */
		pxd = (pxd_t *) & p->slot[stbl[index]];
		bn = addressPXD(pxd);
		psize = lengthPXD(pxd) << JFS_SBI(ip->i_sb)->l2bsize;

		/* unpin the parent page */
		DT_PUTPAGE(mp);
	}

      out:
	DT_PUTPAGE(mp);

      dtSearch_Exit1:

	kfree(ciKey.name);

      dtSearch_Exit2:

	return rc;
}