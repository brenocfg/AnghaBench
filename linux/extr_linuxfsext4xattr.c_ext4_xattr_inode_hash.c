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
struct ext4_sb_info {int /*<<< orphan*/  s_csum_seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_chksum (struct ext4_sb_info*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static u32
ext4_xattr_inode_hash(struct ext4_sb_info *sbi, const void *buffer, size_t size)
{
	return ext4_chksum(sbi, sbi->s_csum_seed, buffer, size);
}