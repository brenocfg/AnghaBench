#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* mnt; } ;
struct svc_export {int ex_flags; int ex_layout_types; TYPE_2__ ex_path; } ;
struct super_block {TYPE_6__* s_bdev; TYPE_3__* s_export_op; } ;
struct TYPE_12__ {TYPE_5__* bd_disk; } ;
struct TYPE_11__ {int /*<<< orphan*/  queue; TYPE_4__* fops; } ;
struct TYPE_10__ {scalar_t__ pr_ops; } ;
struct TYPE_9__ {scalar_t__ commit_blocks; scalar_t__ map_blocks; scalar_t__ get_uuid; } ;
struct TYPE_7__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 int LAYOUT_BLOCK_VOLUME ; 
 int LAYOUT_FLEX_FILES ; 
 int LAYOUT_SCSI ; 
 int NFSEXP_PNFS ; 
 scalar_t__ blk_queue_scsi_passthrough (int /*<<< orphan*/ ) ; 

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