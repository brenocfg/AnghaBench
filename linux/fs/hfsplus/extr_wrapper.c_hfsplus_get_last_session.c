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
struct super_block {TYPE_3__* s_bdev; } ;
struct TYPE_5__ {scalar_t__ lba; } ;
struct cdrom_tocentry {scalar_t__ cdte_track; int cdte_ctrl; TYPE_1__ cdte_addr; void* cdte_format; } ;
struct TYPE_6__ {scalar_t__ lba; } ;
struct cdrom_multisession {TYPE_2__ addr; scalar_t__ xa_flag; void* addr_format; } ;
typedef  int sector_t ;
struct TYPE_8__ {scalar_t__ session; } ;
struct TYPE_7__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDROMMULTISESSION ; 
 int /*<<< orphan*/  CDROMREADTOCENTRY ; 
 int CDROM_DATA_TRACK ; 
 void* CDROM_LBA ; 
 int EINVAL ; 
 TYPE_4__* HFSPLUS_SB (struct super_block*) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int ioctl_by_bdev (TYPE_3__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int hfsplus_get_last_session(struct super_block *sb,
				    sector_t *start, sector_t *size)
{
	struct cdrom_multisession ms_info;
	struct cdrom_tocentry te;
	int res;

	/* default values */
	*start = 0;
	*size = i_size_read(sb->s_bdev->bd_inode) >> 9;

	if (HFSPLUS_SB(sb)->session >= 0) {
		te.cdte_track = HFSPLUS_SB(sb)->session;
		te.cdte_format = CDROM_LBA;
		res = ioctl_by_bdev(sb->s_bdev,
			CDROMREADTOCENTRY, (unsigned long)&te);
		if (!res && (te.cdte_ctrl & CDROM_DATA_TRACK) == 4) {
			*start = (sector_t)te.cdte_addr.lba << 2;
			return 0;
		}
		pr_err("invalid session number or type of track\n");
		return -EINVAL;
	}
	ms_info.addr_format = CDROM_LBA;
	res = ioctl_by_bdev(sb->s_bdev, CDROMMULTISESSION,
		(unsigned long)&ms_info);
	if (!res && ms_info.xa_flag)
		*start = (sector_t)ms_info.addr.lba << 2;
	return 0;
}