#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* cs_nffree; void* cs_nifree; } ;
struct TYPE_11__ {TYPE_3__ fs_u2; } ;
struct ufs_super_block_third {TYPE_4__ fs_un1; } ;
struct TYPE_8__ {scalar_t__ fs_maxbsize; void* cs_nbfree; void* cs_ndir; } ;
struct TYPE_9__ {TYPE_1__ fs_u2; } ;
struct ufs_super_block_second {TYPE_2__ fs_un; } ;
struct TYPE_12__ {void* cs_nffree; void* cs_nifree; void* cs_nbfree; void* cs_ndir; } ;
struct ufs_super_block_first {scalar_t__ fs_bsize; TYPE_5__ fs_cstotal; } ;
struct TYPE_13__ {int /*<<< orphan*/  cs_nffree; int /*<<< orphan*/  cs_nifree; int /*<<< orphan*/  cs_nbfree; int /*<<< orphan*/  cs_ndir; } ;
struct ufs_sb_private_info {TYPE_6__ cs_total; } ;
struct super_block {int dummy; } ;
struct TYPE_14__ {unsigned int s_mount_opt; struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFSD (char*) ; 
 unsigned int UFS_MOUNT_UFSTYPE ; 
 unsigned int UFS_MOUNT_UFSTYPE_44BSD ; 
 unsigned int UFS_MOUNT_UFSTYPE_UFS2 ; 
 TYPE_7__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  USPI_UBH (struct ufs_sb_private_info*) ; 
 void* cpu_to_fs32 (struct super_block*,int /*<<< orphan*/ ) ; 
 void* cpu_to_fs64 (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ufs_super_block_first* ubh_get_usb_first (struct ufs_sb_private_info*) ; 
 struct ufs_super_block_second* ubh_get_usb_second (struct ufs_sb_private_info*) ; 
 struct ufs_super_block_third* ubh_get_usb_third (struct ufs_sb_private_info*) ; 
 int /*<<< orphan*/  ubh_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_print_super_stuff (struct super_block*,struct ufs_super_block_first*,struct ufs_super_block_second*,struct ufs_super_block_third*) ; 

__attribute__((used)) static void ufs_put_cstotal(struct super_block *sb)
{
	unsigned mtype = UFS_SB(sb)->s_mount_opt & UFS_MOUNT_UFSTYPE;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	struct ufs_super_block_first *usb1;
	struct ufs_super_block_second *usb2;
	struct ufs_super_block_third *usb3;

	UFSD("ENTER\n");
	usb1 = ubh_get_usb_first(uspi);
	usb2 = ubh_get_usb_second(uspi);
	usb3 = ubh_get_usb_third(uspi);

	if (mtype == UFS_MOUNT_UFSTYPE_UFS2) {
		/*we have statistic in different place, then usual*/
		usb2->fs_un.fs_u2.cs_ndir =
			cpu_to_fs64(sb, uspi->cs_total.cs_ndir);
		usb2->fs_un.fs_u2.cs_nbfree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nbfree);
		usb3->fs_un1.fs_u2.cs_nifree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nifree);
		usb3->fs_un1.fs_u2.cs_nffree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nffree);
		goto out;
	}

	if (mtype == UFS_MOUNT_UFSTYPE_44BSD &&
	     (usb2->fs_un.fs_u2.fs_maxbsize == usb1->fs_bsize)) {
		/* store stats in both old and new places */
		usb2->fs_un.fs_u2.cs_ndir =
			cpu_to_fs64(sb, uspi->cs_total.cs_ndir);
		usb2->fs_un.fs_u2.cs_nbfree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nbfree);
		usb3->fs_un1.fs_u2.cs_nifree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nifree);
		usb3->fs_un1.fs_u2.cs_nffree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nffree);
	}
	usb1->fs_cstotal.cs_ndir = cpu_to_fs32(sb, uspi->cs_total.cs_ndir);
	usb1->fs_cstotal.cs_nbfree = cpu_to_fs32(sb, uspi->cs_total.cs_nbfree);
	usb1->fs_cstotal.cs_nifree = cpu_to_fs32(sb, uspi->cs_total.cs_nifree);
	usb1->fs_cstotal.cs_nffree = cpu_to_fs32(sb, uspi->cs_total.cs_nffree);
out:
	ubh_mark_buffer_dirty(USPI_UBH(uspi));
	ufs_print_super_stuff(sb, usb1, usb2, usb3);
	UFSD("EXIT\n");
}