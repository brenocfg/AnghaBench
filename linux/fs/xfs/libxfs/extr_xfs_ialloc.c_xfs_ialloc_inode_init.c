#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_ino_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int xfs_agblock_t ;
typedef  scalar_t__ uint ;
struct xfs_trans {int dummy; } ;
struct TYPE_3__ {int sb_inodelog; int /*<<< orphan*/  sb_meta_uuid; int /*<<< orphan*/  sb_inodesize; } ;
struct xfs_mount {int m_bsize; TYPE_1__ m_sb; int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_dinode {int di_version; int /*<<< orphan*/  di_uuid; int /*<<< orphan*/  di_ino; void* di_next_unlinked; void* di_gen; int /*<<< orphan*/  di_magic; } ;
struct xfs_buf {int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_length; int /*<<< orphan*/ * b_ops; } ;
struct list_head {int dummy; } ;
struct TYPE_4__ {int blocks_per_cluster; int inodes_per_cluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBTOB (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 TYPE_2__* M_IGEO (struct xfs_mount*) ; 
 unsigned int NULLAGINO ; 
 int /*<<< orphan*/  XBF_DONE ; 
 int /*<<< orphan*/  XBF_UNMAPPED ; 
 int /*<<< orphan*/  XFS_AGB_TO_AGINO (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_AGB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XFS_AGINO_TO_INO (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DINODE_MAGIC ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_delwri_queue (struct xfs_buf*,struct list_head*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_zero (struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dinode_calc_crc (struct xfs_mount*,struct xfs_dinode*) ; 
 scalar_t__ xfs_dinode_size (int) ; 
 int /*<<< orphan*/  xfs_icreate_log (struct xfs_trans*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  xfs_inode_buf_ops ; 
 struct xfs_dinode* xfs_make_iptr (struct xfs_mount*,struct xfs_buf*,int) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 
 struct xfs_buf* xfs_trans_get_buf (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_inode_alloc_buf (struct xfs_trans*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,struct xfs_buf*,int,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_ordered_buf (struct xfs_trans*,struct xfs_buf*) ; 

int
xfs_ialloc_inode_init(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct list_head	*buffer_list,
	int			icount,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	xfs_agblock_t		length,
	unsigned int		gen)
{
	struct xfs_buf		*fbuf;
	struct xfs_dinode	*free;
	int			nbufs;
	int			version;
	int			i, j;
	xfs_daddr_t		d;
	xfs_ino_t		ino = 0;

	/*
	 * Loop over the new block(s), filling in the inodes.  For small block
	 * sizes, manipulate the inodes in buffers  which are multiples of the
	 * blocks size.
	 */
	nbufs = length / M_IGEO(mp)->blocks_per_cluster;

	/*
	 * Figure out what version number to use in the inodes we create.  If
	 * the superblock version has caught up to the one that supports the new
	 * inode format, then use the new inode version.  Otherwise use the old
	 * version so that old kernels will continue to be able to use the file
	 * system.
	 *
	 * For v3 inodes, we also need to write the inode number into the inode,
	 * so calculate the first inode number of the chunk here as
	 * XFS_AGB_TO_AGINO() only works within a filesystem block, not
	 * across multiple filesystem blocks (such as a cluster) and so cannot
	 * be used in the cluster buffer loop below.
	 *
	 * Further, because we are writing the inode directly into the buffer
	 * and calculating a CRC on the entire inode, we have ot log the entire
	 * inode so that the entire range the CRC covers is present in the log.
	 * That means for v3 inode we log the entire buffer rather than just the
	 * inode cores.
	 */
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		version = 3;
		ino = XFS_AGINO_TO_INO(mp, agno, XFS_AGB_TO_AGINO(mp, agbno));

		/*
		 * log the initialisation that is about to take place as an
		 * logical operation. This means the transaction does not
		 * need to log the physical changes to the inode buffers as log
		 * recovery will know what initialisation is actually needed.
		 * Hence we only need to log the buffers as "ordered" buffers so
		 * they track in the AIL as if they were physically logged.
		 */
		if (tp)
			xfs_icreate_log(tp, agno, agbno, icount,
					mp->m_sb.sb_inodesize, length, gen);
	} else
		version = 2;

	for (j = 0; j < nbufs; j++) {
		/*
		 * Get the block.
		 */
		d = XFS_AGB_TO_DADDR(mp, agno, agbno +
				(j * M_IGEO(mp)->blocks_per_cluster));
		fbuf = xfs_trans_get_buf(tp, mp->m_ddev_targp, d,
					 mp->m_bsize *
					 M_IGEO(mp)->blocks_per_cluster,
					 XBF_UNMAPPED);
		if (!fbuf)
			return -ENOMEM;

		/* Initialize the inode buffers and log them appropriately. */
		fbuf->b_ops = &xfs_inode_buf_ops;
		xfs_buf_zero(fbuf, 0, BBTOB(fbuf->b_length));
		for (i = 0; i < M_IGEO(mp)->inodes_per_cluster; i++) {
			int	ioffset = i << mp->m_sb.sb_inodelog;
			uint	isize = xfs_dinode_size(version);

			free = xfs_make_iptr(mp, fbuf, i);
			free->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
			free->di_version = version;
			free->di_gen = cpu_to_be32(gen);
			free->di_next_unlinked = cpu_to_be32(NULLAGINO);

			if (version == 3) {
				free->di_ino = cpu_to_be64(ino);
				ino++;
				uuid_copy(&free->di_uuid,
					  &mp->m_sb.sb_meta_uuid);
				xfs_dinode_calc_crc(mp, free);
			} else if (tp) {
				/* just log the inode core */
				xfs_trans_log_buf(tp, fbuf, ioffset,
						  ioffset + isize - 1);
			}
		}

		if (tp) {
			/*
			 * Mark the buffer as an inode allocation buffer so it
			 * sticks in AIL at the point of this allocation
			 * transaction. This ensures the they are on disk before
			 * the tail of the log can be moved past this
			 * transaction (i.e. by preventing relogging from moving
			 * it forward in the log).
			 */
			xfs_trans_inode_alloc_buf(tp, fbuf);
			if (version == 3) {
				/*
				 * Mark the buffer as ordered so that they are
				 * not physically logged in the transaction but
				 * still tracked in the AIL as part of the
				 * transaction and pin the log appropriately.
				 */
				xfs_trans_ordered_buf(tp, fbuf);
			}
		} else {
			fbuf->b_flags |= XBF_DONE;
			xfs_buf_delwri_queue(fbuf, buffer_list);
			xfs_buf_relse(fbuf);
		}
	}
	return 0;
}