#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct ovl_layer {TYPE_2__* fs; scalar_t__ fsid; } ;
struct kstat {unsigned int ino; int /*<<< orphan*/  dev; } ;
struct dentry {TYPE_1__* d_inode; TYPE_3__* d_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pseudo_dev; } ;
struct TYPE_5__ {unsigned int i_ino; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int ovl_same_sb (TYPE_3__*) ; 
 unsigned int ovl_xino_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ovl_map_dev_ino(struct dentry *dentry, struct kstat *stat,
			   struct ovl_layer *lower_layer)
{
	bool samefs = ovl_same_sb(dentry->d_sb);
	unsigned int xinobits = ovl_xino_bits(dentry->d_sb);

	if (samefs) {
		/*
		 * When all layers are on the same fs, all real inode
		 * number are unique, so we use the overlay st_dev,
		 * which is friendly to du -x.
		 */
		stat->dev = dentry->d_sb->s_dev;
		return 0;
	} else if (xinobits) {
		unsigned int shift = 64 - xinobits;
		/*
		 * All inode numbers of underlying fs should not be using the
		 * high xinobits, so we use high xinobits to partition the
		 * overlay st_ino address space. The high bits holds the fsid
		 * (upper fsid is 0). This way overlay inode numbers are unique
		 * and all inodes use overlay st_dev. Inode numbers are also
		 * persistent for a given layer configuration.
		 */
		if (stat->ino >> shift) {
			pr_warn_ratelimited("overlayfs: inode number too big (%pd2, ino=%llu, xinobits=%d)\n",
					    dentry, stat->ino, xinobits);
		} else {
			if (lower_layer)
				stat->ino |= ((u64)lower_layer->fsid) << shift;

			stat->dev = dentry->d_sb->s_dev;
			return 0;
		}
	}

	/* The inode could not be mapped to a unified st_ino address space */
	if (S_ISDIR(dentry->d_inode->i_mode)) {
		/*
		 * Always use the overlay st_dev for directories, so 'find
		 * -xdev' will scan the entire overlay mount and won't cross the
		 * overlay mount boundaries.
		 *
		 * If not all layers are on the same fs the pair {real st_ino;
		 * overlay st_dev} is not unique, so use the non persistent
		 * overlay st_ino for directories.
		 */
		stat->dev = dentry->d_sb->s_dev;
		stat->ino = dentry->d_inode->i_ino;
	} else if (lower_layer && lower_layer->fsid) {
		/*
		 * For non-samefs setup, if we cannot map all layers st_ino
		 * to a unified address space, we need to make sure that st_dev
		 * is unique per lower fs. Upper layer uses real st_dev and
		 * lower layers use the unique anonymous bdev assigned to the
		 * lower fs.
		 */
		stat->dev = lower_layer->fs->pseudo_dev;
	}

	return 0;
}