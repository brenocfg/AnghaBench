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
typedef  int /*<<< orphan*/  u32 ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_SUPER_MAGIC ; 
 int /*<<< orphan*/  __f2fs_crc32 (struct f2fs_sb_info*,int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static inline u32 f2fs_crc32(struct f2fs_sb_info *sbi, const void *address,
			   unsigned int length)
{
	return __f2fs_crc32(sbi, F2FS_SUPER_MAGIC, address, length);
}