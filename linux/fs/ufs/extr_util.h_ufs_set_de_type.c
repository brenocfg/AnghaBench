#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d_type; } ;
struct TYPE_5__ {TYPE_1__ d_44; } ;
struct ufs_dir_entry {TYPE_2__ d_u; } ;
struct super_block {int dummy; } ;
struct TYPE_6__ {int s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_BLK ; 
 int /*<<< orphan*/  DT_CHR ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_FIFO ; 
 int /*<<< orphan*/  DT_LNK ; 
 int /*<<< orphan*/  DT_REG ; 
 int /*<<< orphan*/  DT_SOCK ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int UFS_DE_44BSD ; 
 int UFS_DE_MASK ; 
 TYPE_3__* UFS_SB (struct super_block*) ; 

__attribute__((used)) static inline void
ufs_set_de_type(struct super_block *sb, struct ufs_dir_entry *de, int mode)
{
	if ((UFS_SB(sb)->s_flags & UFS_DE_MASK) != UFS_DE_44BSD)
		return;

	/*
	 * TODO turn this into a table lookup
	 */
	switch (mode & S_IFMT) {
	case S_IFSOCK:
		de->d_u.d_44.d_type = DT_SOCK;
		break;
	case S_IFLNK:
		de->d_u.d_44.d_type = DT_LNK;
		break;
	case S_IFREG:
		de->d_u.d_44.d_type = DT_REG;
		break;
	case S_IFBLK:
		de->d_u.d_44.d_type = DT_BLK;
		break;
	case S_IFDIR:
		de->d_u.d_44.d_type = DT_DIR;
		break;
	case S_IFCHR:
		de->d_u.d_44.d_type = DT_CHR;
		break;
	case S_IFIFO:
		de->d_u.d_44.d_type = DT_FIFO;
		break;
	default:
		de->d_u.d_44.d_type = DT_UNKNOWN;
	}
}