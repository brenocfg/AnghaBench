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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  fs_npsect; } ;
struct TYPE_7__ {TYPE_1__ fs_sunx86; } ;
struct ufs_super_block_third {TYPE_2__ fs_un2; } ;
struct TYPE_8__ {int /*<<< orphan*/  fs_npsect; } ;
struct TYPE_9__ {TYPE_3__ fs_sun; } ;
struct ufs_super_block_first {TYPE_4__ fs_u1; } ;
struct super_block {int dummy; } ;
struct TYPE_10__ {int s_flags; } ;

/* Variables and functions */
 TYPE_5__* UFS_SB (struct super_block*) ; 
 int UFS_ST_MASK ; 
 int UFS_ST_SUNx86 ; 
 int /*<<< orphan*/  fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
ufs_get_fs_npsect(struct super_block *sb, struct ufs_super_block_first *usb1,
		  struct ufs_super_block_third *usb3)
{
	if ((UFS_SB(sb)->s_flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		return fs32_to_cpu(sb, usb3->fs_un2.fs_sunx86.fs_npsect);
	else
		return fs32_to_cpu(sb, usb1->fs_u1.fs_sun.fs_npsect);
}