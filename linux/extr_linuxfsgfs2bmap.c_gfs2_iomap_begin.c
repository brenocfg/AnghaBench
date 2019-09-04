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
struct metapath {int mp_aheight; int /*<<< orphan*/ * mp_bh; } ;
struct iomap {scalar_t__ type; int /*<<< orphan*/  private; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct gfs2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOTBLK ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 unsigned int IOMAP_DIRECT ; 
 int /*<<< orphan*/  IOMAP_F_BUFFER_HEAD ; 
 scalar_t__ IOMAP_MAPPED ; 
 unsigned int IOMAP_WRITE ; 
 int /*<<< orphan*/  get_bh (int /*<<< orphan*/ ) ; 
 int gfs2_iomap_begin_write (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct iomap*,struct metapath*) ; 
 int gfs2_iomap_get (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct iomap*,struct metapath*) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 
 int /*<<< orphan*/  trace_gfs2_iomap_end (struct gfs2_inode*,struct iomap*,int) ; 
 int /*<<< orphan*/  trace_gfs2_iomap_start (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int gfs2_iomap_begin(struct inode *inode, loff_t pos, loff_t length,
			    unsigned flags, struct iomap *iomap)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct metapath mp = { .mp_aheight = 1, };
	int ret;

	iomap->flags |= IOMAP_F_BUFFER_HEAD;

	trace_gfs2_iomap_start(ip, pos, length, flags);
	if ((flags & IOMAP_WRITE) && !(flags & IOMAP_DIRECT)) {
		ret = gfs2_iomap_begin_write(inode, pos, length, flags, iomap, &mp);
	} else {
		ret = gfs2_iomap_get(inode, pos, length, flags, iomap, &mp);

		/*
		 * Silently fall back to buffered I/O for stuffed files or if
		 * we've hot a hole (see gfs2_file_direct_write).
		 */
		if ((flags & IOMAP_WRITE) && (flags & IOMAP_DIRECT) &&
		    iomap->type != IOMAP_MAPPED)
			ret = -ENOTBLK;
	}
	if (!ret) {
		get_bh(mp.mp_bh[0]);
		iomap->private = mp.mp_bh[0];
	}
	release_metapath(&mp);
	trace_gfs2_iomap_end(ip, iomap, ret);
	return ret;
}