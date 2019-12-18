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
struct inomap {TYPE_2__* im_agctl; int /*<<< orphan*/  im_l2nbperiext; int /*<<< orphan*/  im_nbperiext; int /*<<< orphan*/  im_numfree; int /*<<< orphan*/  im_numinos; int /*<<< orphan*/  im_nextiag; int /*<<< orphan*/  im_freeiag; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct dinomap_disk {TYPE_1__* in_agctl; void* in_l2nbperiext; void* in_nbperiext; void* in_numfree; void* in_numinos; void* in_nextiag; void* in_freeiag; } ;
struct TYPE_8__ {struct inomap* i_imap; } ;
struct TYPE_7__ {int l2nbperpage; } ;
struct TYPE_6__ {int /*<<< orphan*/  numfree; int /*<<< orphan*/  numinos; int /*<<< orphan*/  extfree; int /*<<< orphan*/  inofree; } ;
struct TYPE_5__ {void* numfree; void* numinos; void* extfree; void* inofree; } ;

/* Variables and functions */
 int EIO ; 
 int IMAPBLKNO ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int MAXAG ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diWriteSpecial (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 struct metapage* get_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

int diSync(struct inode *ipimap)
{
	struct dinomap_disk *dinom_le;
	struct inomap *imp = JFS_IP(ipimap)->i_imap;
	struct metapage *mp;
	int index;

	/*
	 * write imap global conrol page
	 */
	/* read the on-disk inode map control structure */
	mp = get_metapage(ipimap,
			  IMAPBLKNO << JFS_SBI(ipimap->i_sb)->l2nbperpage,
			  PSIZE, 0);
	if (mp == NULL) {
		jfs_err("diSync: get_metapage failed!");
		return -EIO;
	}

	/* copy the in-memory version to the on-disk version */
	dinom_le = (struct dinomap_disk *) mp->data;
	dinom_le->in_freeiag = cpu_to_le32(imp->im_freeiag);
	dinom_le->in_nextiag = cpu_to_le32(imp->im_nextiag);
	dinom_le->in_numinos = cpu_to_le32(atomic_read(&imp->im_numinos));
	dinom_le->in_numfree = cpu_to_le32(atomic_read(&imp->im_numfree));
	dinom_le->in_nbperiext = cpu_to_le32(imp->im_nbperiext);
	dinom_le->in_l2nbperiext = cpu_to_le32(imp->im_l2nbperiext);
	for (index = 0; index < MAXAG; index++) {
		dinom_le->in_agctl[index].inofree =
		    cpu_to_le32(imp->im_agctl[index].inofree);
		dinom_le->in_agctl[index].extfree =
		    cpu_to_le32(imp->im_agctl[index].extfree);
		dinom_le->in_agctl[index].numinos =
		    cpu_to_le32(imp->im_agctl[index].numinos);
		dinom_le->in_agctl[index].numfree =
		    cpu_to_le32(imp->im_agctl[index].numfree);
	}

	/* write out the control structure */
	write_metapage(mp);

	/*
	 * write out dirty pages of imap
	 */
	filemap_write_and_wait(ipimap->i_mapping);

	diWriteSpecial(ipimap, 0);

	return (0);
}