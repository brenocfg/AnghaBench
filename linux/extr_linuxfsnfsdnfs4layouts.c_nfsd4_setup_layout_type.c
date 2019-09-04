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
struct svc_export {int ex_flags; } ;

/* Variables and functions */
 int NFSEXP_PNFS ; 

void nfsd4_setup_layout_type(struct svc_export *exp)
{
#if defined(CONFIG_NFSD_BLOCKLAYOUT) || defined(CONFIG_NFSD_SCSILAYOUT)
	struct super_block *sb = exp->ex_path.mnt->mnt_sb;
#endif

	if (!(exp->ex_flags & NFSEXP_PNFS))
		return;

#ifdef CONFIG_NFSD_FLEXFILELAYOUT
	exp->ex_layout_types |= 1 << LAYOUT_FLEX_FILES;
#endif
#ifdef CONFIG_NFSD_BLOCKLAYOUT
	if (sb->s_export_op->get_uuid &&
	    sb->s_export_op->map_blocks &&
	    sb->s_export_op->commit_blocks)
		exp->ex_layout_types |= 1 << LAYOUT_BLOCK_VOLUME;
#endif
#ifdef CONFIG_NFSD_SCSILAYOUT
	if (sb->s_export_op->map_blocks &&
	    sb->s_export_op->commit_blocks &&
	    sb->s_bdev && sb->s_bdev->bd_disk->fops->pr_ops &&
		blk_queue_scsi_passthrough(sb->s_bdev->bd_disk->queue))
		exp->ex_layout_types |= 1 << LAYOUT_SCSI;
#endif
}