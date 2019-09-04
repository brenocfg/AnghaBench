#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct metapage {scalar_t__ data; } ;
struct inomap {struct inode* im_ipimap; TYPE_1__* im_agctl; void* im_l2nbperiext; void* im_nbperiext; int /*<<< orphan*/  im_numfree; int /*<<< orphan*/  im_numinos; void* im_nextiag; void* im_freeiag; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dinomap_disk {TYPE_2__* in_agctl; int /*<<< orphan*/  in_l2nbperiext; int /*<<< orphan*/  in_nbperiext; int /*<<< orphan*/  in_numfree; int /*<<< orphan*/  in_numinos; int /*<<< orphan*/  in_nextiag; int /*<<< orphan*/  in_freeiag; } ;
struct TYPE_8__ {struct inomap* i_imap; } ;
struct TYPE_7__ {int l2nbperpage; } ;
struct TYPE_6__ {int /*<<< orphan*/  numfree; int /*<<< orphan*/  numinos; int /*<<< orphan*/  extfree; int /*<<< orphan*/  inofree; } ;
struct TYPE_5__ {void* numfree; void* numinos; void* extfree; void* inofree; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG_LOCK_INIT (struct inomap*,int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IAGFREE_LOCK_INIT (struct inomap*) ; 
 int IMAPBLKNO ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int MAXAG ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  kfree (struct inomap*) ; 
 struct inomap* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct metapage* read_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 

int diMount(struct inode *ipimap)
{
	struct inomap *imap;
	struct metapage *mp;
	int index;
	struct dinomap_disk *dinom_le;

	/*
	 * allocate/initialize the in-memory inode map control structure
	 */
	/* allocate the in-memory inode map control structure. */
	imap = kmalloc(sizeof(struct inomap), GFP_KERNEL);
	if (imap == NULL) {
		jfs_err("diMount: kmalloc returned NULL!");
		return -ENOMEM;
	}

	/* read the on-disk inode map control structure. */

	mp = read_metapage(ipimap,
			   IMAPBLKNO << JFS_SBI(ipimap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	if (mp == NULL) {
		kfree(imap);
		return -EIO;
	}

	/* copy the on-disk version to the in-memory version. */
	dinom_le = (struct dinomap_disk *) mp->data;
	imap->im_freeiag = le32_to_cpu(dinom_le->in_freeiag);
	imap->im_nextiag = le32_to_cpu(dinom_le->in_nextiag);
	atomic_set(&imap->im_numinos, le32_to_cpu(dinom_le->in_numinos));
	atomic_set(&imap->im_numfree, le32_to_cpu(dinom_le->in_numfree));
	imap->im_nbperiext = le32_to_cpu(dinom_le->in_nbperiext);
	imap->im_l2nbperiext = le32_to_cpu(dinom_le->in_l2nbperiext);
	for (index = 0; index < MAXAG; index++) {
		imap->im_agctl[index].inofree =
		    le32_to_cpu(dinom_le->in_agctl[index].inofree);
		imap->im_agctl[index].extfree =
		    le32_to_cpu(dinom_le->in_agctl[index].extfree);
		imap->im_agctl[index].numinos =
		    le32_to_cpu(dinom_le->in_agctl[index].numinos);
		imap->im_agctl[index].numfree =
		    le32_to_cpu(dinom_le->in_agctl[index].numfree);
	}

	/* release the buffer. */
	release_metapage(mp);

	/*
	 * allocate/initialize inode allocation map locks
	 */
	/* allocate and init iag free list lock */
	IAGFREE_LOCK_INIT(imap);

	/* allocate and init ag list locks */
	for (index = 0; index < MAXAG; index++) {
		AG_LOCK_INIT(imap, index);
	}

	/* bind the inode map inode and inode map control structure
	 * to each other.
	 */
	imap->im_ipimap = ipimap;
	JFS_IP(ipimap)->i_imap = imap;

	return (0);
}