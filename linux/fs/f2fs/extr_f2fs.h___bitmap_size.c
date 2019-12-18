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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  sit_ver_bitmap_bytesize; int /*<<< orphan*/  nat_ver_bitmap_bytesize; } ;

/* Variables and functions */
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 int NAT_BITMAP ; 
 int SIT_BITMAP ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long __bitmap_size(struct f2fs_sb_info *sbi, int flag)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);

	/* return NAT or SIT bitmap */
	if (flag == NAT_BITMAP)
		return le32_to_cpu(ckpt->nat_ver_bitmap_bytesize);
	else if (flag == SIT_BITMAP)
		return le32_to_cpu(ckpt->sit_ver_bitmap_bytesize);

	return 0;
}