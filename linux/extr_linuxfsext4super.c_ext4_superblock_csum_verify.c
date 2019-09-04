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
struct super_block {int dummy; } ;
struct ext4_super_block {scalar_t__ s_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_has_metadata_csum (struct super_block*) ; 
 scalar_t__ ext4_superblock_csum (struct super_block*,struct ext4_super_block*) ; 

__attribute__((used)) static int ext4_superblock_csum_verify(struct super_block *sb,
				       struct ext4_super_block *es)
{
	if (!ext4_has_metadata_csum(sb))
		return 1;

	return es->s_checksum == ext4_superblock_csum(sb, es);
}