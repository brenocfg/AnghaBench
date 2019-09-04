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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int /*<<< orphan*/ * fs_qbmask; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fs_qbmask; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fs_qbmask; } ;
struct TYPE_9__ {TYPE_3__ fs_44; TYPE_2__ fs_sunx86; TYPE_1__ fs_sun; } ;
struct ufs_super_block_third {TYPE_4__ fs_un2; } ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __fs64 ;
typedef  int /*<<< orphan*/  __fs32 ;
struct TYPE_10__ {int s_flags; } ;

/* Variables and functions */
 TYPE_5__* UFS_SB (struct super_block*) ; 
#define  UFS_ST_44BSD 131 
 int UFS_ST_MASK ; 
#define  UFS_ST_SUN 130 
#define  UFS_ST_SUNOS 129 
#define  UFS_ST_SUNx86 128 
 int /*<<< orphan*/  fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64
ufs_get_fs_qbmask(struct super_block *sb, struct ufs_super_block_third *usb3)
{
	__fs64 tmp;

	switch (UFS_SB(sb)->s_flags & UFS_ST_MASK) {
	case UFS_ST_SUNOS:
	case UFS_ST_SUN:
		((__fs32 *)&tmp)[0] = usb3->fs_un2.fs_sun.fs_qbmask[0];
		((__fs32 *)&tmp)[1] = usb3->fs_un2.fs_sun.fs_qbmask[1];
		break;
	case UFS_ST_SUNx86:
		((__fs32 *)&tmp)[0] = usb3->fs_un2.fs_sunx86.fs_qbmask[0];
		((__fs32 *)&tmp)[1] = usb3->fs_un2.fs_sunx86.fs_qbmask[1];
		break;
	case UFS_ST_44BSD:
		((__fs32 *)&tmp)[0] = usb3->fs_un2.fs_44.fs_qbmask[0];
		((__fs32 *)&tmp)[1] = usb3->fs_un2.fs_44.fs_qbmask[1];
		break;
	}

	return fs64_to_cpu(sb, tmp);
}